// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WeaponSelectButtonUserWidget.h"

#include "Actor/Projectile/BaseProjectile.h"
#include "Actor/Weapon/BaseWeapon.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UWeaponSelectButtonUserWidget::InitButton(UTexture2D* WeaponIcon, const FString& WeaponNameString,
                                               TSubclassOf<ABaseWeapon> WeaponClass)
{
	if (WeaponName)
	{
		WeaponName->SetText(FText::FromString(WeaponNameString));
	}

	if (WeaponImage)
	{
		WeaponImage->SetBrushFromTexture(WeaponIcon);
	}

	if (WeaponClass)
	{
		ButtonWeaponClass = WeaponClass;
		if (SelectButton)
		{
			SelectButton->OnClicked.AddDynamic(this, &UWeaponSelectButtonUserWidget::ButtonWeaponClick);
		}
	}
}

void UWeaponSelectButtonUserWidget::InitButton(UTexture2D* WeaponIcon, const FString& WeaponNameString,
	TSubclassOf<ABaseProjectile> ProjectileClass)
{
	if (WeaponName)
	{
		WeaponName->SetText(FText::FromString(WeaponNameString));
	}

	if (WeaponImage)
	{
		WeaponImage->SetBrushFromTexture(WeaponIcon);
		ProjectileTexture = WeaponIcon;
	}

	if (ProjectileClass)
	{
		ButtonProjectileClass = ProjectileClass;
		if (SelectButton)
		{
			SelectButton->OnClicked.AddDynamic(this, &UWeaponSelectButtonUserWidget::ButtonProjectileClick);
		}
	}
}

void UWeaponSelectButtonUserWidget::ButtonWeaponClick()
{
	if (ButtonWeaponClass)
	{
		OnButtonWeaponSelectButtonClick.Broadcast(ButtonWeaponClass);
	}
}

void UWeaponSelectButtonUserWidget::ButtonProjectileClick()
{
	if (ButtonProjectileClass && WeaponImage)
	{
		OnButtonProjectileSelectButtonClick.Broadcast(ButtonProjectileClass, ProjectileTexture);
	}
}

