// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HitEffectUserWidget.h"
#include "Components/Image.h"


void UHitEffectUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UHitEffectUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetCollapsed();
}

void UHitEffectUserWidget::SetVisible(bool bIsKill)
{
	if (FeedbackImageCollapsedTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(FeedbackImageCollapsedTimerHandle);
	}

	if (bIsKill)
	{
		FeedbackImage->SetBrushTintColor(FSlateColor(KillEnemyEffectColor));
	}
	else
	{
		FeedbackImage->SetBrushTintColor(FSlateColor(NormalEnemyEffectColor));
	}

	FeedbackImage->SetVisibility(ESlateVisibility::Visible);

	FeedbackImage->SetRenderTransformAngle(FMath::FRandRange(HitEffectRotateMin, HitEffectRotateMax));

	GetWorld()->GetTimerManager().SetTimer
	(
		FeedbackImageCollapsedTimerHandle,
		this,
		&UHitEffectUserWidget::SetCollapsed,
		EffectCollapsedTime,
		false
	);
}

void UHitEffectUserWidget::SetCollapsed()
{
	FeedbackImage->SetVisibility(ESlateVisibility::Collapsed);
}
