// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/TDMHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/GameStartCoolDownUserWidget.h"
#include "UI/KillLogUserWidget.h"
#include "UI/PlayerDeathUserWidget.h"
#include "UI/PlayerMainUserWidget.h"
#include "UI/TDMEndUserWidget.h"
#include "UI/WaitGamePlayUserWidget.h"
#include "UI/WeaponSelectUserWidget.h"

void ATDMHUD::BeginPlay()
{
	Super::BeginPlay();

	KillLogWidget = CreateKillLogWidget();

	if (KillLogWidget)
		KillLogWidget->AddToViewport();
}

UKillLogUserWidget* ATDMHUD::CreateKillLogWidget() const
{
	return Cast<UKillLogUserWidget>(CreateWidget(GetOwningPlayerController(), KillLogWidgetClass));
}

UPlayerDeathUserWidget* ATDMHUD::CreatePlayerDeathWidget() const
{
	return Cast<UPlayerDeathUserWidget>(CreateWidget(GetOwningPlayerController(), PlayerDeathWidgetClass));
}

UWaitGamePlayUserWidget* ATDMHUD::CreateWaitGamePlayUserWidget() const
{
	return Cast<UWaitGamePlayUserWidget>(CreateWidget(GetOwningPlayerController(), WaitGamePlayWidgetClass));
}

UGameStartCoolDownUserWidget* ATDMHUD::CreateGameStartCoolDownWidget() const
{
	return Cast<UGameStartCoolDownUserWidget>(CreateWidget(GetOwningPlayerController(), GameStartCoolDownWidgetClass));
}

UTDMEndUserWidget* ATDMHUD::CreateTDMEndUserWidget() const
{
	return Cast<UTDMEndUserWidget>(CreateWidget(GetOwningPlayerController(), TDMEndUserWidgetClass));
}



void ATDMHUD::AddKillLogWidget(const FString& KillPlayerName, int32 KillPlayerPartyNum, UTexture2D* WeaponTexture, int32 DeathPlayerPartyNum, const FString& DeathPlayerName)
{
	if (!KillLogWidget)
	{
		KillLogWidget = CreateKillLogWidget();
		KillLogWidget->AddToViewport();
	}
	
	KillLogWidget->AddKillLog(KillPlayerName, KillPlayerPartyNum, WeaponTexture, DeathPlayerPartyNum, DeathPlayerName);

	GetWorldTimerManager().SetTimer(
		KillLogTimer,
		this,
		&ATDMHUD::ClearKillLogWidget,
		3.f,
		false
	);
}

void ATDMHUD::ClearKillLogWidget()
{
	if (!KillLogWidget)
		return;

	KillLogWidget->ClearKillLog();
}

void ATDMHUD::OwnerDeathUI(const FString& KillPlayerName)
{
	if (PlayerMainUserWidget)
		PlayerMainUserWidget->SetVisibility(ESlateVisibility::Hidden);
	
	if (!PlayerDeathWidget)
	{
		PlayerDeathWidget = CreatePlayerDeathWidget();
		PlayerDeathWidget->AddToViewport();
	}
	
	PlayerDeathWidget->SetKillUserName(KillPlayerName);
	PlayerDeathWidget->SetVisibility(ESlateVisibility::Visible);
}

void ATDMHUD::OwnerRespawn()
{
	if (PlayerMainUserWidget)
		PlayerMainUserWidget->SetVisibility(ESlateVisibility::Visible);
	
	if (!PlayerDeathWidget)
	{
		PlayerDeathWidget = CreatePlayerDeathWidget();
		PlayerDeathWidget->AddToViewport();
	}
	
	PlayerDeathWidget->SetVisibility(ESlateVisibility::Hidden);
}

bool ATDMHUD::OpenOrCloseWeaponSelectUI()
{
	// if (PlayerDeathWidget)
	// 	PlayerDeathWidget->SetVisibility(ESlateVisibility::Hidden);
	return Super::OpenOrCloseWeaponSelectUI();
}



void ATDMHUD::SetGameModeAndMapName(const FText& NewGameModeName, const FText& NewMapName)
{
	if (!WaitGamePlayWidgetWidget)
	{
		WaitGamePlayWidgetWidget = CreateWaitGamePlayUserWidget();
		WaitGamePlayWidgetWidget->AddToViewport();
	}
	WaitGamePlayWidgetWidget->SetVisibility(ESlateVisibility::Visible);
	WaitGamePlayWidgetWidget->SetGameModeAndMapName(NewGameModeName, NewMapName);
}

void ATDMHUD::SetPlayerCountInGameReadyWidget(int32 PlayerCount, int32 MinimumPlayers)
{
	if (!WaitGamePlayWidgetWidget)
	{
		WaitGamePlayWidgetWidget = CreateWaitGamePlayUserWidget();
		WaitGamePlayWidgetWidget->AddToViewport();
	}
	WaitGamePlayWidgetWidget->SetVisibility(ESlateVisibility::Visible);
	WaitGamePlayWidgetWidget->SetCurrentPlayerCount(PlayerCount, MinimumPlayers);
}

void ATDMHUD::RemoveGameReadyWidget()
{
	if (!WaitGamePlayWidgetWidget)
		return;

	WaitGamePlayWidgetWidget->RemoveFromViewport();
}

void ATDMHUD::SetGamePlayCoolDown(int32 CoolTime)
{
	if (!GameStartCoolDownWidget)
	{
		GameStartCoolDownWidget = CreateGameStartCoolDownWidget();
		GameStartCoolDownWidget->AddToViewport();
	}
	//GameStartCoolDownWidgetWidget->SetVisibility(ESlateVisibility::Visible);
	GameStartCoolDownWidget->StartCoolDown(CoolTime);
}

void ATDMHUD::RemoveGamePlayCoolDownWidget()
{
	if (!GameStartCoolDownWidget)
		return;

	GameStartCoolDownWidget->RemoveFromViewport();
}

void ATDMHUD::InitGameEndUserWidget(int32 RedTeamScore, int32 BlueTeamScore, bool bIsWin, UTexture2D* GameIcon)
{
	if (!TDMEndUserWidget)
	{
		TDMEndUserWidget = CreateTDMEndUserWidget();
		TDMEndUserWidget->AddToViewport();
	}
	TDMEndUserWidget->InitGameEndWidget(RedTeamScore, BlueTeamScore, bIsWin, GameIcon);
}

void ATDMHUD::RemoveGameEndUserWidget()
{
	if (!TDMEndUserWidget)
		return;

	TDMEndUserWidget->RemoveFromViewport();
}
