// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/KillLogTextUserWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"


void UKillLogTextUserWidget::InitKillLowText(const FString& KillPlayerName, int32 KillPlayerPartyNum,
                                             UTexture2D* WeaponTexture, int32 DeathPlayerPartyNum, const FString& DeathPlayerName)
{
	FSlateColor KillPlayerSlateColor;
	FSlateColor DeathPlayerSlateColor;
	
	switch (KillPlayerPartyNum)
	{
	case 0:
		KillPlayerSlateColor = FSlateColor(FLinearColor::Green);
		break;
	case 1:
		KillPlayerSlateColor = FSlateColor(FLinearColor::Red);
		break;
	case 2:
		KillPlayerSlateColor = FSlateColor(FLinearColor::Blue);
		break;
	default:
		KillPlayerSlateColor = FSlateColor(FLinearColor::White);
		;
	}

	switch (DeathPlayerPartyNum)
	{
	case 0:
		DeathPlayerSlateColor = FSlateColor(FLinearColor::Green);
		break;
	case 1:
		DeathPlayerSlateColor = FSlateColor(FLinearColor::Red);
		break;
	case 2:
		DeathPlayerSlateColor = FSlateColor(FLinearColor::Blue);
		break;
	default:
		DeathPlayerSlateColor = FSlateColor(FLinearColor::White);
		;
	}

	if (KillPlayerUserNameText)
	{
		KillPlayerUserNameText->SetText(FText::FromString(KillPlayerName));
		KillPlayerUserNameText->SetColorAndOpacity(KillPlayerSlateColor);
	}
	if (WeaponImage)
	{
		WeaponImage->SetBrushFromTexture(WeaponTexture);
	}
	if (DeathPlayerUserNameText)
	{
		DeathPlayerUserNameText->SetText(FText::FromString(DeathPlayerName));
		DeathPlayerUserNameText->SetColorAndOpacity(DeathPlayerSlateColor);
	}
	if (ShowKillLog)
		PlayAnimation(ShowKillLog);
	
}

void UKillLogTextUserWidget::GoDown()
{
	
}
