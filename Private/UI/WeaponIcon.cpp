// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WeaponIcon.h"

#include "Components/Image.h"

void UWeaponIcon::SetWeapon(UTexture2D* WeaponIcon, int AttachmentCount)
{
	WeaponImage->SetBrushFromTexture(WeaponIcon, false);
}

void UWeaponIcon::SetWeaponIcon(UTexture2D* WeaponIcon)
{
	WeaponImage->SetBrushFromTexture(WeaponIcon, false);
}
