// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/KillLogUserWidget.h"

#include "Components/ScrollBox.h"
#include "UI/KillLogTextUserWidget.h"


void UKillLogUserWidget::AddKillLog_Implementation(const FString& KillPlayerName, int32 KillPlayerPartyNum,
	UTexture2D* WeaponTexture, int32 DeathPlayerPartyNum, const FString& DeathPlayerName)
{
	if (!KillLogTextClass)
		return;

	UKillLogTextUserWidget* NewKillLogText = Cast<UKillLogTextUserWidget>(CreateWidget<UKillLogTextUserWidget>(GetOwningPlayer(), KillLogTextClass));

	if (!NewKillLogText)
		return;

	KillLogScrollBox->ClearChildren();

	KillLogScrollBox->AddChild(NewKillLogText);
	NewKillLogText->InitKillLowText(KillPlayerName, KillPlayerPartyNum, WeaponTexture, DeathPlayerPartyNum, DeathPlayerName);
	KillLogScrollBox->ScrollToStart();

	for (int32 i = KillLogTextArr.Num() -1; i >= KillLogTextArr.Num() -5; i--)
	{
		if (KillLogTextArr.IsValidIndex(i))
			KillLogScrollBox->AddChild(KillLogTextArr[i]);
	}
	
	KillLogTextArr.Add(NewKillLogText);

	
}

void UKillLogUserWidget::ClearKillLog()
{
	KillLogScrollBox->ClearChildren();
	KillLogTextArr.Empty();
}
