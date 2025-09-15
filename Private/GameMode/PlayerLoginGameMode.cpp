// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PlayerLoginGameMode.h"

#include "Actor/Weapon/BaseWeapon.h"
#include "Character/FPSUILogicCharacter.h"
#include "Controller/FPSLoginLogicController.h"
#include "Controller/FPSUILogicController.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetGuidLibrary.h"

DEFINE_LOG_CATEGORY(LOG_PlayerLoginGameMode);

void APlayerLoginGameMode::BeginPlay()
{
	Super::BeginPlay();

	bUseSeamlessTravel = true;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass() ,PlayerStartPointArr);


	
}

APawn* APlayerLoginGameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
	return nullptr;
}

void APlayerLoginGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// if (AFPSActionLogicController* NewFPSPlayer = Cast<AFPSActionLogicController>(NewPlayer))
	// {
	// 	PlayerLogin(NewFPSPlayer);
	// }
}

FString APlayerLoginGameMode::GetClientIPAddress(APlayerController* PlayerController)
{
	if (PlayerController && PlayerController->GetNetConnection())
	{
		FString IP = PlayerController->GetNetConnection()->RemoteAddressToString();
		return IP;
	}
	
	return TEXT("Unknown IP");
}

void APlayerLoginGameMode::PlayerLogin(AFPSLoginLogicController* LoginPlayerController, const FString& NickName,
	const FString& LoginID)
{
	if (!LoginPlayerController)
		return;

	if (UKismetSystemLibrary::IsPackagedForDistribution() && CheckMultiClient(LoginPlayerController, LoginID))
	{
		// 패키징 된 것이고 다클라면
		if (LoginPlayerController->GetNetConnection())
		{
			// 접속 종료
			UE_LOG(LOG_PlayerLoginGameMode, Error, TEXT("플레이어가 다클라일 경우 접속 종료"));
			LoginPlayerController->GetNetConnection()->Close();
			return;
		}
		else
		{
			// 이런경우가 일어날 수 있나요?
		}
	}

	if (!SpawnPlayer(LoginPlayerController))
	{
		UE_LOG(LOG_PlayerLoginGameMode, Error, TEXT("LoginPlayerController or PlayerStartPointArr[StartPointIndex] is not valid"));
	}

	AddParty(LoginPlayerController, NickName, LoginID);
	
}

bool APlayerLoginGameMode::CheckMultiClient(AFPSLoginLogicController* LoginPlayerController, const FString& LoginID)
{
	bool bIsMultiClient = false;

	if (!LoginPlayerController)
		return bIsMultiClient;
	
	for (FPlayerAccountInfo PlayerInfo : LoginPlayerInfoArr)
	{
		if (PlayerInfo.GetPlayerIPAddress() == GetClientIPAddress(LoginPlayerController) && PlayerInfo.GetPlayerLoginID() == LoginID)
		{
			// IP와 로그인 아이디가 같으면
			bIsMultiClient = true;
			break;
		}
	}

	return bIsMultiClient;
}

void APlayerLoginGameMode::AddParty(AFPSLoginLogicController* LoginPlayerController, const FString& NickName,
	const FString& LoginID)
{
	FPlayerAccountInfo NewPlayerAccountInfo = FPlayerAccountInfo();
	NewPlayerAccountInfo.SetGuid(UKismetGuidLibrary::NewGuid());
	NewPlayerAccountInfo.SetPlayerController(LoginPlayerController);
	NewPlayerAccountInfo.SetPlayerNickName(NickName);
	NewPlayerAccountInfo.SetPlayerLoginID(LoginID);
	NewPlayerAccountInfo.SetPlayerIPAddress(GetClientIPAddress(LoginPlayerController));
	
	NewPlayerAccountInfo.SetPartyIndex(PartyArr.Num());
	NewPlayerAccountInfo.SetPlayerIndex(0);
	
	FParty NewParty = FParty();
	NewParty.AddPlayer(NewPlayerAccountInfo);

	PartyArr.Add(NewParty);

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
	
	
}

bool APlayerLoginGameMode::SpawnPlayer(AFPSLoginLogicController* LoginPlayerController)
{
	if (!LoginPlayerController || !PlayerStartPointArr.IsValidIndex(StartPointIndex))
	{
		UE_LOG(LOG_PlayerLoginGameMode, Error, TEXT("LoginPlayerController or PlayerStartPointArr[StartPointIndex] is not valid"));
		return false;
	}

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;
	UClass* PawnClass = GetDefaultPawnClassForController(LoginPlayerController);
	APawn* ResultPawn = GetWorld()->SpawnActor<APawn>(PawnClass, PlayerStartPointArr[StartPointIndex]->GetActorTransform(), SpawnInfo);

	if (!ResultPawn)
	{
		UE_LOG(LOG_PlayerLoginGameMode, Error, TEXT("플레이어 폰 스폰 실패"));
		return false;
	}

	AFPSUILogicCharacter* PlayerPawn = Cast<AFPSUILogicCharacter>(ResultPawn);

	if (LoginPlayerController->GetSubWeaponClass())
	{
		LoginPlayerController->SpawnWeaponAndEquipToSub(LoginPlayerController->GetSubWeaponClass());
	}
	
	if (LoginPlayerController->GetMainWeaponClass())
	{
		LoginPlayerController->SpawnWeaponAndEquipToMain(LoginPlayerController->GetMainWeaponClass());
	}

	
	
	if (!PlayerPawn)
	{
		UE_LOG(LOG_PlayerLoginGameMode, Error, TEXT("왜 디폴트 폰이 AFPSUILogicCharacter가 아닌겁니까?"));
		return false;
	}

	LoginPlayerController->Possess(PlayerPawn);

	StartPointIndex++;

	
	
	return true;
}

FTransform APlayerLoginGameMode::GetPlayerRespawnTransform(AFPSActionLogicController* RespawnPlayerController)
{
	int32 RandomStartActorIndex = FMath::RandRange(0, PlayerStartPointArr.Num() -1);

	if (PlayerStartPointArr.IsValidIndex(RandomStartActorIndex))
	{
		return PlayerStartPointArr[RandomStartActorIndex]->GetActorTransform();
	}
	else
	{
		return FTransform();
	}
}

void APlayerLoginGameMode::RespawnPlayer(AFPSActionLogicController* RespawnPlayerController)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;
	UClass* PawnClass = GetDefaultPawnClassForController(RespawnPlayerController);
	APawn* ResultPawn = GetWorld()->SpawnActor<APawn>(PawnClass, GetPlayerRespawnTransform(RespawnPlayerController), SpawnInfo);
	
	if (!ResultPawn)
	{
		UE_LOG(LOG_PlayerLoginGameMode, Error, TEXT("플레이어 폰 스폰 실패"));
		return;
	}

	AFPSUILogicCharacter* PlayerPawn = Cast<AFPSUILogicCharacter>(ResultPawn);
	
	if (!PlayerPawn)
	{
		UE_LOG(LOG_PlayerLoginGameMode, Error, TEXT("왜 디폴트 폰이 AFPSUILogicCharacter가 아닌겁니까?"));
		return;
	}
	
	RespawnPlayerController->Possess(PlayerPawn);

	if (RespawnPlayerController->GetMainWeaponClass())
		RespawnPlayerController->SpawnWeaponAndEquipToMain(RespawnPlayerController->GetMainWeaponClass());

	if (RespawnPlayerController->GetSubWeaponClass())
		RespawnPlayerController->SpawnWeaponAndEquipToSub(RespawnPlayerController->GetSubWeaponClass());
	
	
}




