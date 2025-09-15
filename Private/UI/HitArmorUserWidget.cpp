// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HitArmorUserWidget.h"

#include "Components/Image.h"

void UHitArmorUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UHitArmorUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetArmorEffectCollapsed();
}

void UHitArmorUserWidget::SetArmorEffectVisible(bool bIsCrush)
{
	if (ArmorImageCollapsedTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ArmorImageCollapsedTimerHandle);
	}

	if (bIsCrush)
	{
		ArmorImage->SetBrushFromTexture(CrushArmorTexture);
	}
	else
	{
		ArmorImage->SetBrushFromTexture(HitArmorTexture);
	}

	ArmorImage->SetVisibility(ESlateVisibility::Visible);

	GetWorld()->GetTimerManager().SetTimer
	(
		ArmorImageCollapsedTimerHandle,
		this,
		&UHitArmorUserWidget::SetArmorEffectCollapsed,
		ArmorImageCollapsedTime,
		false
	);
}


void UHitArmorUserWidget::SetArmorEffectCollapsed()
{
	ArmorImage->SetVisibility(ESlateVisibility::Collapsed);
}
