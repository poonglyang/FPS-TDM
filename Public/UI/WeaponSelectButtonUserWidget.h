// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponSelectButtonUserWidget.generated.h"

class ABaseProjectile;
class ABaseWeapon;
class UTexture2D;
class UButton;
class UTextBlock;
class UImage;

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonWeaponSelectButtonClick, TSubclassOf<ABaseWeapon>, WeaponClass);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonProjectileSelectButtonClick, TSubclassOf<ABaseProjectile>, WeaponClass, UTexture2D*, ProjectileTexture);

UCLASS()
class BATTLEROYAL_API UWeaponSelectButtonUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitButton(UTexture2D* WeaponIcon, const FString& WeaponNameString, TSubclassOf<ABaseWeapon> WeaponClass);

	void InitButton(UTexture2D* WeaponIcon, const FString& WeaponNameString, TSubclassOf<ABaseProjectile> ProjectileClass);

protected:
	UFUNCTION()
	virtual void ButtonWeaponClick();

	UFUNCTION()
	virtual void ButtonProjectileClick();
public:
	FOnButtonWeaponSelectButtonClick OnButtonWeaponSelectButtonClick;
	FOnButtonProjectileSelectButtonClick OnButtonProjectileSelectButtonClick; 
	
protected:
	UPROPERTY(meta=(BindWidget))
	UButton* SelectButton;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* WeaponName;

	UPROPERTY(meta=(BindWidget))
	UImage* WeaponImage;

	UPROPERTY()
	UTexture2D* ProjectileTexture;
	
	UPROPERTY()
	TSubclassOf<ABaseWeapon> ButtonWeaponClass;

	UPROPERTY()
	TSubclassOf<ABaseProjectile> ButtonProjectileClass;
};
