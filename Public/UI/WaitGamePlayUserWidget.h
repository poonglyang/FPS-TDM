// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WaitGamePlayUserWidget.generated.h"

/**
 * 
 */

class UTextBlock;

UCLASS()
class BATTLEROYAL_API UWaitGamePlayUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Wait GamePlay UserWidget")
	void SetGameModeAndMapName(const FText& NewGameModeName, const FText& NewMapName);

	UFUNCTION(BlueprintCallable, Category = "Wait GamePlay UserWidget")
	void SetCurrentPlayerCount(int32 PlayerCount, int32 MinimumPlayers);
	
protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UTextBlock* MapName;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UTextBlock* ModeName;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UTextBlock* PlayerNum;
};
