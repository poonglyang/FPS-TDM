// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KillLogTextUserWidget.generated.h"

/**
 * 
 */
class UTexture2D;
class UImage;
class UTextBlock;
class UWidgetAnimation;

UCLASS()
class BATTLEROYAL_API UKillLogTextUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void InitKillLowText(const FString& KillPlayerName, int32 KillPlayerPartyNum, UTexture2D* WeaponTexture, int32 DeathPlayerPartyNum, const FString& DeathPlayerName);
	
	virtual void GoDown();

protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillPlayerUserNameText;

	UPROPERTY(meta = (BindWidget))
	UImage* WeaponImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DeathPlayerUserNameText;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ShowKillLog;
};
