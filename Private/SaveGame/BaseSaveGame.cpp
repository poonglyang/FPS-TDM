// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGame/BaseSaveGame.h"

#include "Kismet/GameplayStatics.h"

FString UBaseSaveGame::GetNickName()
{
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("세이브 게임으로 들어온 닉네임 : %s"), *NickName));
	return NickName;
}

void UBaseSaveGame::SetNickName(const FString& NewNickName)
{
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("세이브 게임으로 반환한 닉네임 : %s"), *NickName));
	NickName = NewNickName;
}
