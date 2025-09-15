// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HitEffectUserWidget.generated.h"

/**
 * 
 */
class UImage;

UCLASS()
class BATTLEROYAL_API UHitEffectUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
public:
	UFUNCTION(BlueprintCallable, Category = "HitEffectUserWidget")
	virtual void SetVisible(bool bIsKill);

	UFUNCTION(BlueprintCallable, Category = "HitEffectUserWidget")
	virtual void SetCollapsed();
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitEffectUserWidget", meta = (BindWidget))
	UImage* FeedbackImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitEffectUserWidget")
	FTimerHandle FeedbackImageCollapsedTimerHandle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitEffectUserWidget")
	FLinearColor KillEnemyEffectColor = FLinearColor(0.541f, 0.f, 0.f, 1.f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitEffectUserWidget")
	FLinearColor NormalEnemyEffectColor = FLinearColor::White;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitEffectUserWidget")
	float HitEffectRotateMin = -5.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitEffectUserWidget")
	float HitEffectRotateMax = 5.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitEffectUserWidget")
	float EffectCollapsedTime = 0.1f;
};
