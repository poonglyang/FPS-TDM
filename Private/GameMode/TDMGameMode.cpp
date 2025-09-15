// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TDMGameMode.h"

#include "Actor/Weapon/BaseWeapon.h"
#include "Character/FPSUILogicCharacter.h"
#include "Controller/FPSLoginLogicController.h"
#include "Controller/FPSUILogicController.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetGuidLibrary.h"

DEFINE_LOG_CATEGORY(LOG_TDMGameMode);

void ATDMGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	for (AActor* PlayerStart : PlayerStartPointArr)
	{
		APlayerStart* CurrentStart = Cast<APlayerStart>(PlayerStart);

		if (!CurrentStart)
			continue;

		if (CurrentStart->PlayerStartTag == FName("BlueTeamSpawn"))
		{
			BlueTeamStartSpawn.Add(CurrentStart);
		}
		else if (CurrentStart->PlayerStartTag == FName("RedTeamSpawn"))
		{
			RedTeamStartSpawn.Add(CurrentStart);
		}
		else
		{
			RandomSpawn.Add(CurrentStart);
		}
	}

	GameStartCoolTime = DefaultGameStartCoolTime;
}

void ATDMGameMode::AddParty(AFPSLoginLogicController* LoginPlayerController, const FString& NickName,
	const FString& LoginID)
{
	//Super::AddParty(LoginPlayerController, NickName, LoginID);
	FPlayerAccountInfo NewPlayerAccountInfo = FPlayerAccountInfo();
	NewPlayerAccountInfo.SetGuid(UKismetGuidLibrary::NewGuid());
	NewPlayerAccountInfo.SetPlayerController(LoginPlayerController);
	NewPlayerAccountInfo.SetPlayerNickName(NickName);
	NewPlayerAccountInfo.SetPlayerLoginID(LoginID);
	NewPlayerAccountInfo.SetPlayerIPAddress(GetClientIPAddress(LoginPlayerController));
	
	if (RedTeam.Num() <= BlueTeam.Num())
	{
		NewPlayerAccountInfo.SetPartyIndex(1);
		NewPlayerAccountInfo.SetPlayerIndex(RedTeam.Num());
		RedTeam.Add(NewPlayerAccountInfo);
	}
	else
	{
		NewPlayerAccountInfo.SetPartyIndex(2);
		NewPlayerAccountInfo.SetPlayerIndex(BlueTeam.Num());
		BlueTeam.Add(NewPlayerAccountInfo);
	}
	
	LoginPlayerInfoArr.Add(NewPlayerAccountInfo);
	LoginPlayerController->SetPlayerAccountInfo(NewPlayerAccountInfo);
	
	AFPSUILogicController* UIPlayerController = Cast<AFPSUILogicController>(LoginPlayerController);

	if (!UIPlayerController)
		return;

	UIPlayerController->SetOwnerPlayerIndexAndNickName(NewPlayerAccountInfo.GetPlayerIndex(), NewPlayerAccountInfo.GetPlayerNickName());
	if (AFPSUILogicCharacter* CurrentPawn = Cast<AFPSUILogicCharacter>(UIPlayerController->GetPawn()))
	{
		UIPlayerController->SetOwnerHpAndArmorUI(
			CurrentPawn->CharacterState.GetHp()/ CurrentPawn->CharacterState.GetMaxHp(),
			CurrentPawn->CharacterState.GetArmor()/ CurrentPawn->CharacterState.GetMaxArmor()
		);
	}
	
	FTimerHandle UpdatePartyTimerHandle;

	if (NewPlayerAccountInfo.GetPartyIndex() == 1)
	{
		GetWorldTimerManager().SetTimer(
		UpdatePartyTimerHandle,
		this,
		&ATDMGameMode::UpdateRedTeamPartyInfo,
		0.5f,
		false
		);
	}
	else
	{
		GetWorldTimerManager().SetTimer(
		UpdatePartyTimerHandle,
		this,
		&ATDMGameMode::UpdateBlueTeamPartyInfo,
		0.5f,
		false
		);
	}
	
	if (!LoginPlayerController->GetPawn())
		return;

	AActor* SpawnPointActor = nullptr;
	
	if (LoginPlayerController->GetPlayerAccountInfo().GetPartyIndex() == 1 && RedTeamStartSpawn.Num() != 0 && RedTeamStartSpawn.IsValidIndex(RedTeamStartPointIndex%RedTeamStartSpawn.Num()))
	{
		SpawnPointActor = RedTeamStartSpawn[RedTeamStartPointIndex%RedTeamStartSpawn.Num()];
	}
	else if (BlueTeamStartSpawn.Num() != 0  && BlueTeamStartSpawn.IsValidIndex(BlueTeamStartPointIndex%BlueTeamStartSpawn.Num()))
	{
		SpawnPointActor = BlueTeamStartSpawn[BlueTeamStartPointIndex%BlueTeamStartSpawn.Num()];
	}

	if (SpawnPointActor)
	{
		LoginPlayerController->GetPawn()->SetActorLocation(SpawnPointActor->GetActorLocation());
		LoginPlayerController->GetPawn()->SetActorRotation(SpawnPointActor->GetActorRotation());
	}
}

void ATDMGameMode::PlayerLogin(AFPSLoginLogicController* LoginPlayerController, const FString& NickName,
	const FString& LoginID)
{

	if (!LoginPlayerController)
		return;

	if (AFPSUILogicController* CurrentUIController = Cast<AFPSUILogicController>(LoginPlayerController))
	{
		switch (CurrentGameState) {
		case EGameState::GameReady:
			// 게임 대기 창 열기 또는 게임 시작으로 변경

			// 게임 대기 창 띄움
			CurrentUIController->ClientSetGameModeAndMapName(GameModeName, GameMapName);
			CurrentUIController->ClientSetPlayerCountInGameReadyWidget(LoginPlayerInfoArr.Num() + 1, MinimumPlayers);
			UKismetSystemLibrary::PrintString(this, TEXT("대기 화면 띄움"));
			if (LoginPlayerInfoArr.Num() >= MinimumPlayers -1) // -1을 한 이유는 밑에 있는 Super::PlayerLogin() 에서 플레이어가 추가되기 때문
			{
				// 3초 뒤에 게임을 시작함
				if (!RemoveWaitUIHandle.IsValid())
				{
					GetWorldTimerManager().SetTimer(
						RemoveWaitUIHandle,
						this,
						&ATDMGameMode::GameStart,
						3.f,
						false
					);
				}
			}

			for (FPlayerAccountInfo Player : LoginPlayerInfoArr)
			{
				AFPSUILogicController* CurrentPlayerController = Cast<AFPSUILogicController>( Player.GetPlayerController());
				if (!CurrentPlayerController)
					continue;

				CurrentPlayerController->ClientSetPlayerCountInGameReadyWidget(LoginPlayerInfoArr.Num() + 1, MinimumPlayers);
			}
		
			break;
		case EGameState::GameStart:
			// 무기 선택창 띄움
			if (AFPSUILogicController* CurrentController = Cast<AFPSUILogicController>(LoginPlayerController))
			{
				//CurrentController->ClientRemoveGameReadyWidget();
				CurrentController->OpenOrCloseWeaponSelectUI();
			}
			break;
		case EGameState::GameInProgress:
			LoginPlayerController->SetSubWeaponClass(DefaultWeapon); // 기본 무기를 DefaultWeapon으로 하고 스폰시킴
			break;
		case EGameState::GameEnd:
			// 플레이어 접속 종료
		
			if (LoginPlayerController->GetNetConnection())
			{
				// 접속 종료
				UE_LOG(LOG_PlayerLoginGameMode, Warning, TEXT("플레이어가 게임이 종료된 서버에 접속함"));
				LoginPlayerController->GetNetConnection()->Close();
			}
			return;
		}

	}
	
	
	Super::PlayerLogin(LoginPlayerController, NickName, LoginID);
}

void ATDMGameMode::UpdateRedTeamPartyInfo()
{
	for (FPlayerAccountInfo PartyPlayerInfo :  RedTeam)
	{
		AFPSUILogicController* CurrentController = Cast<AFPSUILogicController>(PartyPlayerInfo.GetPlayerController());
		if (!CurrentController)
			continue;

		for (FPlayerAccountInfo PartyAnotherPlayerInfo : RedTeam)
		{
			CurrentController->SetPartyValidPlayerIndexAndNickName(PartyAnotherPlayerInfo.GetPlayerIndex(), PartyAnotherPlayerInfo.GetPlayerNickName());
			CurrentController->SetPartyPlayerArmorAndHealth(
				PartyAnotherPlayerInfo.GetCurrentCharacterHealth() / PartyAnotherPlayerInfo.GetCurrentCharacterMaxHealth(),
				PartyAnotherPlayerInfo.GetCurrentCharacterArmor() / PartyAnotherPlayerInfo.GetCurrentCharacterMaxArmor(),
				PartyAnotherPlayerInfo.GetPlayerIndex()
			);
		}
	}
}

void ATDMGameMode::UpdateBlueTeamPartyInfo()
{
	for (FPlayerAccountInfo PartyPlayerInfo :  BlueTeam)
	{
		AFPSUILogicController* CurrentController = Cast<AFPSUILogicController>(PartyPlayerInfo.GetPlayerController());
		if (!CurrentController)
			continue;

		for (FPlayerAccountInfo PartyAnotherPlayerInfo : BlueTeam)
		{
			CurrentController->SetPartyValidPlayerIndexAndNickName(PartyAnotherPlayerInfo.GetPlayerIndex(), PartyAnotherPlayerInfo.GetPlayerNickName());
			CurrentController->SetPartyPlayerArmorAndHealth(
				PartyAnotherPlayerInfo.GetCurrentCharacterHealth() / PartyAnotherPlayerInfo.GetCurrentCharacterMaxHealth(),
				PartyAnotherPlayerInfo.GetCurrentCharacterArmor() / PartyAnotherPlayerInfo.GetCurrentCharacterMaxArmor(),
				PartyAnotherPlayerInfo.GetPlayerIndex()
			);
		}
	}
}

void ATDMGameMode::PlayerDead(AFPSUILogicController* DeadPlayerController,
	AFPSUILogicController* AttackPlayerController, UTexture2D* WeaponTexture)
{
	FString KillPlayerName = AttackPlayerController->GetPlayerAccountInfo().GetPlayerNickName();
	int32 KillPlayerPartyNum = AttackPlayerController->GetPlayerAccountInfo().GetPartyIndex();
	FString DeathPlayerName = DeadPlayerController->GetPlayerAccountInfo().GetPlayerNickName();
	int32 DeathPlayerPartyNum = DeadPlayerController->GetPlayerAccountInfo().GetPartyIndex();

	KillPlayerPartyNum == 1 ? RedTeamScore++ : BlueTeamScore++;
	
	for (FPlayerAccountInfo Player : LoginPlayerInfoArr)
	{
		AFPSUILogicController* CurrentPlayerController = Cast<AFPSUILogicController>( Player.GetPlayerController());
		if (!CurrentPlayerController)
			continue;

		bool bIsAttackPlayer = AttackPlayerController == CurrentPlayerController ? true : false;
		bool bIsDeathPlayer = DeadPlayerController == CurrentPlayerController ? true : false;

		if (bIsAttackPlayer && bIsDeathPlayer)
		{
			CurrentPlayerController->ClientAddKillLog(KillPlayerName, KillLogSelf, WeaponTexture, KillLogSelf, DeathPlayerName);
		}
		else if (bIsAttackPlayer)
		{
			CurrentPlayerController->ClientAddKillLog(KillPlayerName, KillLogSelf, WeaponTexture, DeathPlayerPartyNum, DeathPlayerName);
		}
		else if (bIsDeathPlayer)
		{
			CurrentPlayerController->ClientAddKillLog(KillPlayerName, KillPlayerPartyNum, WeaponTexture, KillLogSelf, DeathPlayerName);
		}
		else
		{
			CurrentPlayerController->ClientAddKillLog(KillPlayerName, KillPlayerPartyNum, WeaponTexture, DeathPlayerPartyNum, DeathPlayerName);
		}

		CurrentPlayerController->ClientSetPartyScore(BlueTeamScore, RedTeamScore, TargetScore);
	}

	switch (CurrentGameState) {
	case EGameState::GameReady:
		UE_LOG(LOG_TDMGameMode, Error, TEXT("아니 게임 준비중인데 킬이 왜 나와요"));
		break;
	case EGameState::GameStart:
		UE_LOG(LOG_TDMGameMode, Error, TEXT("아니 게임 시작 대기 중인데 킬이 왜 나와요"));
		break;
	case EGameState::GameInProgress:
		if (TargetScore == BlueTeamScore || TargetScore == RedTeamScore)
		{
			GameEnd();
		}
		break;
	case EGameState::GameEnd:
		break;
	}
}

void ATDMGameMode::GameStart()
{
	CurrentGameState = EGameState::GameStart;
	for (FPlayerAccountInfo Player : LoginPlayerInfoArr)
	{
		if (AFPSUILogicController* CurrentController = Cast<AFPSUILogicController>( Player.GetPlayerController()))
		{
			CurrentController->ClientRemoveGameReadyWidget();
			CurrentController->OpenOrCloseWeaponSelectUI();
		}
	}
	
	GetWorldTimerManager().SetTimer(
		GameStarTTimerHandle,
		this,
		&ATDMGameMode::GameStartCoolDown,
		1.f,
		true
	);
}

void ATDMGameMode::GameStartCoolDown()
{
	
	for (FPlayerAccountInfo Player : LoginPlayerInfoArr)
	{
		if (AFPSUILogicController* CurrentController = Cast<AFPSUILogicController>( Player.GetPlayerController()))
		{
			CurrentController->ClientSetGameStartCoolDown(GameStartCoolTime);
		}
	}
	
	GameStartCoolTime--;

	if (-1 >= GameStartCoolTime && GameStarTTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(GameStarTTimerHandle);
		GameInProgress();
	}
}

void ATDMGameMode::GameInProgress()
{
	CurrentGameState = EGameState::GameInProgress;
	for (FPlayerAccountInfo Player : LoginPlayerInfoArr)
	{
		if (AFPSUILogicController* CurrentController = Cast<AFPSUILogicController>( Player.GetPlayerController()))
		{
			CurrentController->ClientRemoveGameStartCoolDown();
			CurrentController->CloseWeaponSelectUI();
		}
	}
}

void ATDMGameMode::GameEnd()
{
	CurrentGameState = EGameState::GameEnd;

	int WinTeamIndex;
	RedTeamScore > BlueTeamScore ? WinTeamIndex = 1 : WinTeamIndex = 2;
	
	for (FPlayerAccountInfo Player : LoginPlayerInfoArr)
	{
		if (AFPSUILogicController* CurrentController = Cast<AFPSUILogicController>( Player.GetPlayerController()))
		{
			 CurrentController->ClientGameEndUI(RedTeamScore, BlueTeamScore, Player.GetPartyIndex() == WinTeamIndex, GameIcon);
		}
	}

	FTimerHandle BackToLobbyTimerHandle;
	GetWorldTimerManager().SetTimer(
		BackToLobbyTimerHandle,
		this,
		&ATDMGameMode::BackToLobby,
		InitDelay,
		false
	);

	FTimerHandle InitServerTimerHandle;
	GetWorldTimerManager().SetTimer(
		InitServerTimerHandle,
		this,
		&ATDMGameMode::InitServer,
		InitDelay,
		false
	);
}

void ATDMGameMode::BackToLobby()
{
	for (FPlayerAccountInfo Player : LoginPlayerInfoArr)
	{
		if (AFPSUILogicController* CurrentController = Cast<AFPSUILogicController>( Player.GetPlayerController()))
		{
			CurrentController->MoveToAnotherServer(LobbyServerAddress);
		}
	}
}

void ATDMGameMode::InitServer()
{
	GameStartCoolTime = DefaultGameStartCoolTime;
	RedTeamScore = 0;
	BlueTeamScore = 0;
	LoginPlayerInfoArr.Empty();
	RedTeam.Empty();
	BlueTeam.Empty();
	PartyArr.Empty();

	TArray<AActor*> WeaponArr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseWeapon::StaticClass(), WeaponArr);
	for (AActor* Weapon : WeaponArr)
	{
		Weapon->Destroy();
	}
	
	TArray<AActor*> PlayerCharacterArr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFPSUILogicCharacter::StaticClass(), PlayerCharacterArr);
	for (AActor* Player : PlayerCharacterArr)
	{
		Player->Destroy();
	}

	CurrentGameState = EGameState::GameReady;
}

void ATDMGameMode::UpdateTeamDiscrimination()
{
	UpdateRedTeamDiscrimination();
	UpdateBlueTeamDiscrimination();
}

void ATDMGameMode::UpdateRedTeamDiscrimination()
{
	for (FPlayerAccountInfo Player : RedTeam)
	{
		if (Player.GetPlayerController() && Player.GetPlayerController()->GetPawn())
		{
			if (AFPSUILogicController* UILogicController = Cast<AFPSUILogicController>(Player.GetPlayerController()))
			{
				UILogicController->ClientUpdateFriendIdentification();
			}
		}
	}
}

void ATDMGameMode::UpdateBlueTeamDiscrimination()
{
	for (FPlayerAccountInfo Player : BlueTeam)
	{
		if (Player.GetPlayerController() && Player.GetPlayerController()->GetPawn())
		{
			if (AFPSUILogicController* UILogicController = Cast<AFPSUILogicController>(Player.GetPlayerController()))
			{
				UILogicController->ClientUpdateFriendIdentification();
			}
		}
	}
}


void ATDMGameMode::RespawnPlayer(AFPSActionLogicController* RespawnPlayerController)
{
	Super::RespawnPlayer(RespawnPlayerController);
	AFPSUILogicController* CurrentPlayer = Cast<AFPSUILogicController>(RespawnPlayerController);
	
	if (!CurrentPlayer)
		return;

	CurrentPlayer->SetPawnPartyIndex();
	
	CurrentPlayer->GetPlayerAccountInfo().GetPartyIndex() == 1 ? UpdateRedTeamPartyInfo() : UpdateBlueTeamPartyInfo();

	if (AFPSUILogicCharacter* CurrentPawn = Cast<AFPSUILogicCharacter>(CurrentPlayer->GetPawn()))
	{
		CurrentPlayer->SetOwnerHpAndArmorUI(
			CurrentPawn->CharacterState.GetHp()/ CurrentPawn->CharacterState.GetMaxHp(),
			CurrentPawn->CharacterState.GetArmor()/ CurrentPawn->CharacterState.GetMaxArmor()
		);
	}
	
}
