// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerDeathUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYAL_API UPlayerDeathUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent,  Category = "PlayerDeath UI")
	void SetKillUserName(const FString& KillUserName);
};
