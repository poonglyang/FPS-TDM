// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/PlayerMainHUD.h"
#include "DamageFeedbadkHUD.generated.h"

/**
 * 
 */
class UHitEffectUserWidget;
class UHitArmorUserWidget;
class UDamageFeedbackUserWidget;

UCLASS()
class BATTLEROYAL_API ADamageFeedbadkHUD : public APlayerMainHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;


public:
	virtual void CreateHitEffectWidget();
	
	virtual void CreateHitArmorWidget();

	virtual UDamageFeedbackUserWidget* CreateDamageFeedbackWidget();

	virtual void SetHitEffect(bool bIsKill);

	virtual void SetHitArmor(bool bIsCrush);

	virtual void SetDamageFeedback(FVector HitPos, FVector ShotPos);

	virtual void SetDynamicDamageFeedback(ACharacter* NewAttackPlayer, ACharacter* NewHitPlayer);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMainHUD")
	TSubclassOf<UHitEffectUserWidget> HitEffectUserWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMainHUD")
	UHitEffectUserWidget* HitEffectUserWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMainHUD")
	TSubclassOf<UHitArmorUserWidget> HitArmorUserWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMainHUD")
	UHitArmorUserWidget* HitArmorUserWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMainHUD")
	TSubclassOf<UDamageFeedbackUserWidget> DamageFeedbackUserWidgetClass;

};




