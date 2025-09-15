// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponSelectUserWidget.generated.h"

/**
 * 
 */

class AFPSUILogicController;
class ABaseProjectile;
class ABaseWeapon;
class USelectMainWeaponUserWidget;
class USelectSubWeaponUserWidget;
class UButton;

UCLASS()
class BATTLEROYAL_API UWeaponSelectUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

	virtual AFPSUILogicController* GetFPSUILogicController();
	
	UFUNCTION()
	virtual void SelectMainWeapon(TSubclassOf<ABaseWeapon> MainWeaponClass);

	UFUNCTION()
	virtual void SelectSubWeapon(TSubclassOf<ABaseWeapon> SubWeaponClass);

	UFUNCTION()
	virtual void SelectLethal(TSubclassOf<ABaseProjectile> LethalClass, UTexture2D* ProjectileTexture);
	
	UFUNCTION()
	virtual void SelectTactical(TSubclassOf<ABaseProjectile> TacticalClass, UTexture2D* ProjectileTexture);

	UFUNCTION()
	virtual void SelectCompleteButtonClick();
	

protected:
	UPROPERTY(meta = (BindWidget))
	USelectMainWeaponUserWidget* WBP_SelectMainWeaponUI_v2;

	UPROPERTY(meta = (BindWidget))
	USelectSubWeaponUserWidget* WBP_SelectSubWeaponUI_v2;

	UPROPERTY(meta = (BindWidget))
	UButton* SelectComplete;
	
};
