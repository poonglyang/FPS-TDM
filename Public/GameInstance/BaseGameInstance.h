// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

class UBaseSaveGame;

DECLARE_LOG_CATEGORY_EXTERN(LOG_BaseGameInstance, Log, All);
/**
 * 
 */
UCLASS()
class BATTLEROYAL_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UBaseGameInstance();
	
public:
	UFUNCTION(BlueprintCallable, Category = "UserSession")
	FString GetClientLoginId();

	UFUNCTION(BlueprintCallable, Category = "UserNickName")
	void SaveNickName(const FString& NewNickName);

	UFUNCTION(BlueprintCallable, Category = "UserNickName")
	bool LoadNickName(FString& NickName);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "UserSession")
	FString PCInfo;

	UPROPERTY(BlueprintReadOnly, Category = "UserNickName")
	UBaseSaveGame* BaseSaveGame = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UserNickName")
	FString NickNameSaveSlotName = FString(TEXT("SaveNickName"));
};
