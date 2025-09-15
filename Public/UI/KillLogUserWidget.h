// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KillLogUserWidget.generated.h"

class UScrollBox;
/**
 * 
 */
class UCanvasPanel;

class UKillLogTextUserWidget;

UCLASS()
class BATTLEROYAL_API UKillLogUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "KillLog")
	void AddKillLog(const FString& KillPlayerName, int32 KillPlayerPartyNum, UTexture2D* WeaponTexture, int32 DeathPlayerPartyNum, const FString& DeathPlayerName);

	void ClearKillLog();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KillLog", meta = (BindWidget))
	UScrollBox* KillLogScrollBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KillLog")
	TSubclassOf<UKillLogTextUserWidget> KillLogTextClass = nullptr;

	UPROPERTY()
	TArray<UKillLogTextUserWidget*> KillLogTextArr;
};
