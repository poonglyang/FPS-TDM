// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/FPSLoginLogicController.h"

#include "Character/FPSUILogicCharacter.h"
#include "GameInstance/BaseGameInstance.h"
#include "GameMode/PlayerLoginGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

void AFPSLoginLogicController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSLoginLogicController, PlayerAccountInfo, COND_None, REPNOTIFY_Always);
}

void AFPSLoginLogicController::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		
	}
	else
	{
		if (UBaseGameInstance* CurrentGameInstance = Cast<UBaseGameInstance>(GetGameInstance()))
		{
			// 게임 인스턴스가 있고
			FString NickName;
			if (CurrentGameInstance->LoadNickName(NickName))
			{
				// 닉네임 로드가 완료 되면
				ServerLoginReady(NickName, CurrentGameInstance->GetClientLoginId());
				UKismetSystemLibrary::PrintString(this, NickName);
			}
			else
			{
				// 닉네임 로드가 완료 되면
				ServerLoginReady(FString(TEXT("UnknowNickName")), FString(TEXT("UnknowLoginID")));
			}
		}
	}
}

FPlayerAccountInfo AFPSLoginLogicController::GetPlayerAccountInfo()
{
	return PlayerAccountInfo;
}

void AFPSLoginLogicController::SetPlayerAccountInfo(FPlayerAccountInfo NewPlayerAccountInfo)
{
	PlayerAccountInfo = NewPlayerAccountInfo;
	if (AFPSUILogicCharacter* CurrentPawn = Cast<AFPSUILogicCharacter>(GetPawn()))
	{
		CurrentPawn->SetCharacterTeamNum(PlayerAccountInfo.GetPartyIndex());
	}
}

void AFPSLoginLogicController::SetPawnPartyIndex() const
{
	if (AFPSUILogicCharacter* CurrentPawn = Cast<AFPSUILogicCharacter>(GetPawn()))
	{
		CurrentPawn->SetCharacterTeamNum(PlayerAccountInfo.GetPartyIndex());
	}
}

void AFPSLoginLogicController::ServerLoginReady_Implementation(const FString& NickName, const FString& LoginID)
{
	APlayerLoginGameMode* LoginGameMode = Cast<APlayerLoginGameMode>( UGameplayStatics::GetGameMode(GetWorld()));
	
	if (!LoginGameMode)
	{
		return;
	}

	LoginGameMode->PlayerLogin(this, NickName, LoginID);
}


