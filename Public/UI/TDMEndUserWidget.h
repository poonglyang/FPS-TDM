// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDMEndUserWidget.generated.h"

/**
 * 
 */
class UTexture2D;

UCLASS()
class BATTLEROYAL_API UTDMEndUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void InitGameEndWidget(int32 RedTeamScore, int32 BlueTeamScore, bool bIsWin, UTexture2D* GameIcon);
};
