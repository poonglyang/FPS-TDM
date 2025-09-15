// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlayerMainHUD.h"

#include "Blueprint/UserWidget.h"
#include "Controller/FPSUILogicController.h"
#include "UI/PlayerMainUserWidget.h"
#include "UI/WeaponSelectUserWidget.h"

DEFINE_LOG_CATEGORY(LOG_PlayerMainHUD);

void APlayerMainHUD::BeginPlay()
{
	Super::BeginPlay();

	CreatePlayerMainUserWidget();

	CreateWeaponSelectUserWidget();
}

void APlayerMainHUD::CreatePlayerMainUserWidget()
{
	if (!PlayerMainUserWidgetClass->IsChildOf(UPlayerMainUserWidget::StaticClass()))
	{
		UE_LOG(LOG_PlayerMainHUD, Error, TEXT("UPlayerMainUserWidget을 상속받은 것을 넣어주세요"));
		return;
	}

	if (PlayerMainUserWidget)
	{
		UE_LOG(LOG_PlayerMainHUD, Warning, TEXT("PlayerMainUserWidget은 이미 만들어져 있습니다"));
		return;
	}
	
	PlayerMainUserWidget = Cast<UPlayerMainUserWidget>(CreateWidget(GetOwningPlayerController(), PlayerMainUserWidgetClass));

	if (!PlayerMainUserWidget)
	{
		UE_LOG(LOG_PlayerMainHUD, Error, TEXT("UPlayerMainUserWidget이게 우에 일어납니까...?"));
		return;
	}

	PlayerMainUserWidget->AddToViewport(0);

}

void APlayerMainHUD::CreateWeaponSelectUserWidget()
{
	if (!WeaponSelectUserWidgetClass->IsChildOf(UWeaponSelectUserWidget::StaticClass()))
	{
		UE_LOG(LOG_PlayerMainHUD, Error, TEXT("UWeaponSelectUserWidget을 상속받은 것을 넣어주세요"));
		return;
	}

	if (WeaponSelectUserWidget)
	{
		UE_LOG(LOG_PlayerMainHUD, Warning, TEXT("WeaponSelectUserWidget은 이미 만들어져 있습니다"));
		return;
	}
	
	WeaponSelectUserWidget = Cast<UWeaponSelectUserWidget>(CreateWidget(GetOwningPlayerController(), WeaponSelectUserWidgetClass));

	if (!WeaponSelectUserWidget)
	{
		UE_LOG(LOG_PlayerMainHUD, Error, TEXT("WeaponSelectUserWidget 이게 우에 일어납니까...?"));
		return;
	}
	WeaponSelectUserWidget->AddToViewport(3);
	WeaponSelectUserWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void APlayerMainHUD::SetOwnerPlayerArmorAndHealth(float ArmorPercent, float HealthPercent)
{
	if (!PlayerMainUserWidget)
	{
		CreatePlayerMainUserWidget();
		SetOwnerPlayerArmorAndHealth(ArmorPercent, HealthPercent);
		return;
	}
		
	PlayerMainUserWidget->SetOwnerPlayerArmor(ArmorPercent);
	PlayerMainUserWidget->SetOwnerPlayerHealth(HealthPercent);
	
}

void APlayerMainHUD::SetOwnerPlayerIndexAndNickName(int Index, const FString& NickName)
{
	if (!PlayerMainUserWidget)
	{
		CreatePlayerMainUserWidget();
		SetOwnerPlayerIndexAndNickName(Index, NickName);
		return;
	}

	PlayerMainUserWidget->SetOwnerPlayerIndexAndNickName(Index, NickName);
}

void APlayerMainHUD::SetCurrentWeaponCurrentAmmo(int CurrentWeaponAmmoCount)
{
	if (!PlayerMainUserWidget)
	{
		CreatePlayerMainUserWidget();
		SetCurrentWeaponCurrentAmmo(CurrentWeaponAmmoCount);
		return;
	}
	
	PlayerMainUserWidget->SetCurrentWeaponCurrentAmmo(CurrentWeaponAmmoCount);
}

void APlayerMainHUD::SetCurrentCharacterAmmoCount(int CurrentCharacterAmmoCount)
{
	if (!PlayerMainUserWidget)
	{
		CreatePlayerMainUserWidget();
		SetCurrentCharacterAmmoCount(CurrentCharacterAmmoCount);
		return;
	}
	
	PlayerMainUserWidget->SetCurrentCharacterAmmoCount(CurrentCharacterAmmoCount);
}

void APlayerMainHUD::SetCurrentWeaponIcon(UTexture2D* WeaponIcon)
{
	if (!PlayerMainUserWidget)
	{
		CreatePlayerMainUserWidget();
		SetCurrentWeaponIcon(WeaponIcon);
		return;
	}

	PlayerMainUserWidget->SetCurrentWeaponIcon(WeaponIcon);
}

void APlayerMainHUD::SetLethalImage(UTexture2D* LethalImage)
{
	if (!PlayerMainUserWidget)
	{
		CreatePlayerMainUserWidget();
		SetLethalImage(LethalImage);
		return;
	}

	PlayerMainUserWidget->SetLethalImage(LethalImage);
}

void APlayerMainHUD::SetLethalCount(int LethalCount)
{
	if (!PlayerMainUserWidget)
	{
		CreatePlayerMainUserWidget();
		SetLethalCount(LethalCount);
		return;
	}

	PlayerMainUserWidget->SetLethalCount(LethalCount);
}

void APlayerMainHUD::SetTacticalImage(UTexture2D* TacticalImage)
{
	if (!PlayerMainUserWidget)
	{
		CreatePlayerMainUserWidget();
		SetTacticalImage(TacticalImage);
		return;
	}

	PlayerMainUserWidget->SetTacticalImage(TacticalImage);
}

void APlayerMainHUD::SetTacticalCount(int TacticalCount)
{
	if (!PlayerMainUserWidget)
	{
		CreatePlayerMainUserWidget();
		SetTacticalCount(TacticalCount);
		return;
	}

	PlayerMainUserWidget->SetTacticalCount(TacticalCount);
}

bool APlayerMainHUD::CalcPartyIndex(int OldPartyIndex, int& NewPartyIndex) const
{

	bool bCalcResult = false;
	
	AFPSUILogicController* CurrentController = Cast<AFPSUILogicController>(GetOwningPlayerController());

	if (!CurrentController) 
		return bCalcResult;

	int OwnerPlayerPartyIndex = CurrentController->GetPlayerAccountInfo().GetPlayerIndex();
	
	if (OwnerPlayerPartyIndex == OldPartyIndex)
	{
		// 변경해야 하는 파티원이 나랑 같은거면 취소 나 자기 자신은 SetOwnerPlayerIndexAndNickName으로 변경됨
		return bCalcResult;
	}

	bCalcResult = true;

	if (OldPartyIndex > OwnerPlayerPartyIndex)
	{
		NewPartyIndex = OldPartyIndex - 1;
	}
	else
	{
		NewPartyIndex = OldPartyIndex;
	}

	return bCalcResult;
	
}

void APlayerMainHUD::SetPartyPlayerArmorAndHealth(float HealthPercent, float ArmorPercent, int PartyIndex)
{
	if (!PlayerMainUserWidget)
	{
		CreatePlayerMainUserWidget();
	}

	int CalculatedPartyIndex; 
	
	if (!CalcPartyIndex(PartyIndex, CalculatedPartyIndex))
	{
		return;
	}
	
	switch (CalculatedPartyIndex)
	{
	case 0:
		PlayerMainUserWidget->SetPartyPlayer0HealthAndArmor(HealthPercent, ArmorPercent);
		break;
		
	case 1:
		PlayerMainUserWidget->SetPartyPlayer1HealthAndArmor(HealthPercent, ArmorPercent);
		break;
		
	case 2:
		PlayerMainUserWidget->SetPartyPlayer2HealthAndArmor(HealthPercent, ArmorPercent);
		break;
		
	case 3:
		PlayerMainUserWidget->SetPartyPlayer3HealthAndArmor(HealthPercent, ArmorPercent);
		break;
		
	case 4:
		PlayerMainUserWidget->SetPartyPlayer4HealthAndArmor(HealthPercent, ArmorPercent);
		break;
		
	default: ;
	}

}

void APlayerMainHUD::SetPartyValidPlayerIndexAndNickName(int PartyIndex, const FString& NickName)
{
	if (!PlayerMainUserWidget)
	{
		CreatePlayerMainUserWidget();
	}

	int CalculatedPartyIndex; 
	
	if (!CalcPartyIndex(PartyIndex, CalculatedPartyIndex))
	{
		return;
	}

	switch (CalculatedPartyIndex)
	{
	case 0:
		PlayerMainUserWidget->SetPartyPlayer0IndexAndNickname(PartyIndex, NickName);
		break;
		
	case 1:
		PlayerMainUserWidget->SetPartyPlayer1IndexAndNickname(PartyIndex, NickName);
		break;
		
	case 2:
		PlayerMainUserWidget->SetPartyPlayer2IndexAndNickname(PartyIndex, NickName);
		break;
		
	case 3:
		PlayerMainUserWidget->SetPartyPlayer3IndexAndNickname(PartyIndex, NickName);
		break;
		
	case 4:
		PlayerMainUserWidget->SetPartyPlayer4IndexAndNickname(PartyIndex, NickName);
		break;
		
	default: ;
	}
}

void APlayerMainHUD::SetPartyNotValidPlayerHidden(int PartyIndex)
{
	if (!PlayerMainUserWidget)
	{
		CreatePlayerMainUserWidget();
	}
	
	int CalculatedPartyIndex; 
	
	if (!CalcPartyIndex(PartyIndex, CalculatedPartyIndex))
	{
		return;
	}

	switch (CalculatedPartyIndex)
	{
	case 0:
		PlayerMainUserWidget->SetPartyPlayer0InfoHide();
		break;
		
	case 1:
		PlayerMainUserWidget->SetPartyPlayer1InfoHide();
		break;
		
	case 2:
		PlayerMainUserWidget->SetPartyPlayer2InfoHide();
		break;
		
	case 3:
		PlayerMainUserWidget->SetPartyPlayer3InfoHide();
		break;
		
	case 4:
		PlayerMainUserWidget->SetPartyPlayer4InfoHide();
		break;
		
	default: ;
	}
}

bool APlayerMainHUD::OpenOrCloseWeaponSelectUI()
{
	if (!WeaponSelectUserWidget)
	{
		CreateWeaponSelectUserWidget();
	}

	FInputModeUIOnly InputMode;
	
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	
	//InputMode.SetWidgetToFocus(WeaponSelectUserWidget->TakeWidget());

	
	GetOwningPlayerController()->SetInputMode(InputMode);
	GetOwningPlayerController()->SetShowMouseCursor(true);
	
	if (WeaponSelectUserWidget->GetVisibility() == ESlateVisibility::Collapsed)
	{
		WeaponSelectUserWidget->SetVisibility(ESlateVisibility::Visible);
		return true;
	}
	
	WeaponSelectUserWidget->SetVisibility(ESlateVisibility::Collapsed);
	return false;
		
}

void APlayerMainHUD::CloseWeaponSelectUI()
{
	if (WeaponSelectUserWidget)
		WeaponSelectUserWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void APlayerMainHUD::SetPartyScore(int32 BlueTeamScore, int32 RedTeamScore, int32 TargetScore)
{
	if (!PlayerMainUserWidget)
	{
		CreatePlayerMainUserWidget();
	}

	PlayerMainUserWidget->SetPartyScore(BlueTeamScore, RedTeamScore, TargetScore);
}

void APlayerMainHUD::SetShotTypeIcon(EShotType ShotTypeA, EShotType ShotTypeB)
{
	if (!PlayerMainUserWidget)
	{
		CreatePlayerMainUserWidget();
	}

	PlayerMainUserWidget->SetWeaponShotType(ShotTypeA, ShotTypeB);
}

void APlayerMainHUD::SetShotTypeA()
{
	if (!PlayerMainUserWidget)
	{
		CreatePlayerMainUserWidget();
	}

	PlayerMainUserWidget->SetShotTypeA();
}

void APlayerMainHUD::SetShotTypeB()
{
	if (!PlayerMainUserWidget)
	{
		CreatePlayerMainUserWidget();
	}

	PlayerMainUserWidget->SetShotTypeB();
}
