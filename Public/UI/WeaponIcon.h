// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponIcon.generated.h"

class UImage;
class UTexture2D;
/**
 * 
 */
UCLASS()
class BATTLEROYAL_API UWeaponIcon : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWeapon(UTexture2D* WeaponIcon, int AttachmentCount);

	UFUNCTION(BlueprintCallable)
	void SetWeaponIcon(UTexture2D* WeaponIcon);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UImage* WeaponImage;
};
