// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HitArmorUserWidget.generated.h"

/**
 * 
 */

class UImage;

UCLASS()
class BATTLEROYAL_API UHitArmorUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

	
	virtual void NativeConstruct() override;
public:
	UFUNCTION(BlueprintCallable, Category = "HitArmorUserWidget")
	virtual void SetArmorEffectVisible(bool bIsCrush);

	UFUNCTION(BlueprintCallable, Category = "HitArmorUserWidget")
	virtual void SetArmorEffectCollapsed();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitArmorUserWidget", meta = (BindWidget))
	UImage* ArmorImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitArmorUserWidget")
	FTimerHandle ArmorImageCollapsedTimerHandle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitArmorUserWidget")
	UTexture2D* HitArmorTexture;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitArmorUserWidget")
	UTexture2D* CrushArmorTexture;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HitArmorUserWidget")
	float ArmorImageCollapsedTime = 0.2f;
};
