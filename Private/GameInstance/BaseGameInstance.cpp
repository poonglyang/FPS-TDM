// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/BaseGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SaveGame/BaseSaveGame.h"

DEFINE_LOG_CATEGORY(LOG_BaseGameInstance);

UBaseGameInstance::UBaseGameInstance()
{

}

FString UBaseGameInstance::GetClientLoginId()
{
	if (PCInfo == FString())
	{
		PCInfo = FPlatformMisc::GetLoginId();
	}

	return PCInfo;
}

void UBaseGameInstance::SaveNickName(const FString& NewNickName)
{
	if (!BaseSaveGame)
	{
		BaseSaveGame = Cast<UBaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UBaseSaveGame::StaticClass()));
	}

	if (BaseSaveGame)
	{
		BaseSaveGame->SetNickName(NewNickName);
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("게임 인스턴스로 들어온 닉네임 : %s"), *NewNickName));
		if (!UGameplayStatics::SaveGameToSlot(BaseSaveGame, NickNameSaveSlotName, 0))
		{
			UE_LOG(LOG_BaseGameInstance, Error, TEXT("NickName Save Fail"));
		}
	}
}

bool UBaseGameInstance::LoadNickName(FString& NickName)
{
	bool Result = false;
	
	if (UBaseSaveGame* CurrentSaveGame = Cast<UBaseSaveGame>(UGameplayStatics::LoadGameFromSlot(NickNameSaveSlotName, 0)))
	{
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("세이브 게임이 존재하는가? %s 닉네임 : %s"), *CurrentSaveGame->GetName(), *CurrentSaveGame->GetNickName()));
		NickName = CurrentSaveGame->GetNickName();
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("게임 인스턴스에서 반환받은 닉네임 : %s"), *NickName));
		Result = true;
	}

	return Result;
}
