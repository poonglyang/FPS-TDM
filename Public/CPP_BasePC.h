// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPP_BasePC.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYAL_API ACPP_BasePC : public APlayerController
{
	GENERATED_BODY()
	void PawnLeavingGame() override;

	UFUNCTION(BlueprintCallable)
	void ClientTravelFucntion(FString levelAddress);
};
