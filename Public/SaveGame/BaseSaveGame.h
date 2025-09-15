// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BaseSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYAL_API UBaseSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	FString GetNickName();

	void SetNickName(const FString& NewNickName);
protected:
	UPROPERTY(BlueprintReadWrite, Category="SaveData")
	FString NickName;
};
