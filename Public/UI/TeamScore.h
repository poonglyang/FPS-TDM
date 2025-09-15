// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TeamScore.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYAL_API UTeamScore : public UUserWidget
{
	GENERATED_BODY()
	


public:

	UFUNCTION(BlueprintCallable)
	FString GetTeamNameText(int index);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetTeamNameLength();

	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TeamScore)
	FString TeamName;

	UPROPERTY(BlueprintReadOnly, Category = TeamScore)
	int TeamNameLength;
};
