// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GetPlayerAddress.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYAL_API UGetPlayerAddress : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "UserSession")
	FString GetClientIPAddress(APlayerController* PlayerController);
};
