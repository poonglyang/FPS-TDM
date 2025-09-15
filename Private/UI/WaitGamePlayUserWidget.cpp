// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WaitGamePlayUserWidget.h"

#include "Components/TextBlock.h"


void UWaitGamePlayUserWidget::SetGameModeAndMapName(const FText& NewGameModeName, const FText& NewMapName)
{
	if (!MapName || !ModeName)
		return;

	ModeName->SetText(NewGameModeName);
	MapName->SetText(NewMapName);
}

void UWaitGamePlayUserWidget::SetCurrentPlayerCount(int32 PlayerCount, int32 MinimumPlayers)
{
	if (!PlayerNum)
		return;
	
	PlayerNum->SetText(
		FText::Format(
		NSLOCTEXT("MyNamespace", "MyKey", "플레이어 대기중\n{0} / {1}"),
		FText::AsNumber(PlayerCount), FText::AsNumber(MinimumPlayers) 
		)
	);
}
