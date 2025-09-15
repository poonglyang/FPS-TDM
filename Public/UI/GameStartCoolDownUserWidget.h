// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStartCoolDownUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYAL_API UGameStartCoolDownUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "GameStartCoolDown Widget")
	void StartCoolDown(int CoolTime);
};
