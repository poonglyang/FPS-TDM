// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPP_BaseGM.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYAL_API ACPP_BaseGM : public AGameModeBase
{
	GENERATED_BODY()
	UFUNCTION(BlueprintPure, Category = "UserSession")
	FString GetClientIPAddress(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "UserSession")
	FString GetClientPCName(APlayerController* PlayerController);

public:
	void Logout(AController* Exiting) override;
};


