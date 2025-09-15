// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageFeedbackUserWidget.generated.h"

/**
 * 
 */

class UOverlay;
class UImage;

UCLASS()
class BATTLEROYAL_API UDamageFeedbackUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable, Category = "DamageFeedbackUserWidget")
	virtual void SetHitDamageUI(FVector HitPos, FVector ShotPos);
	
protected:
	float CalculateRotationAngle() const;
	
public:
	UFUNCTION(BlueprintCallable, Category = "DamageFeedbackUserWidget")
	virtual void StartHitDamageFeedback(ACharacter* NewAttackPlayer, ACharacter* NewHitPlayer);
	
	virtual void LoopHitDamageFeedback();

	

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DamageFeedbackUserWidget", meta = (BindWidget))
	UOverlay* DamageOverlay;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DamageFeedbackUserWidget", meta = (BindWidget))
	UImage* DamageImage;

	UPROPERTY()
	FTimerHandle DamageFeedbackLoopTimerHandle;

	UPROPERTY()
	ACharacter* AttackPlayer;

	UPROPERTY()
	ACharacter* HitPlayer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DamageFeedbackUserWidget")
	float LoopTime = 0.03f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DamageFeedbackUserWidget")
	float InterpSpeed = 0.03f;
	
	UPROPERTY()
	float ElapsedTime = 0.0f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DamageFeedbackUserWidget")
	float CollapsedStartTime = 1.5f;

	

	
};
