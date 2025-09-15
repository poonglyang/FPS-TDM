// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WeaponSelectUserWidget.h"

#include "Components/Button.h"
#include "Controller/FPSUILogicController.h"
#include "Controller/FPSWeaponLogicController.h"
#include "UI/SelectMainWeaponUserWidget.h"
#include "UI/SelectSubWeaponUserWidget.h"

void UWeaponSelectUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!WBP_SelectMainWeaponUI_v2 || !WBP_SelectSubWeaponUI_v2 || !SelectComplete)
		return;

	WBP_SelectMainWeaponUI_v2->OnMainWeaponSelectButtonClick.AddDynamic(this, &UWeaponSelectUserWidget::SelectMainWeapon);
	WBP_SelectSubWeaponUI_v2->OnSubWeaponSelectButtonClick.AddDynamic(this, &UWeaponSelectUserWidget::SelectSubWeapon);
	WBP_SelectSubWeaponUI_v2->OnLethalSelectButtonClick.AddDynamic(this, &UWeaponSelectUserWidget::SelectLethal);
	WBP_SelectSubWeaponUI_v2->OnTacticalSelectButtonClick.AddDynamic(this, &UWeaponSelectUserWidget::SelectTactical);

	SelectComplete->OnClicked.AddDynamic(this, &UWeaponSelectUserWidget::SelectCompleteButtonClick);

}

AFPSUILogicController* UWeaponSelectUserWidget::GetFPSUILogicController()
{
	return Cast<AFPSUILogicController>( GetOwningPlayer());
}

void UWeaponSelectUserWidget::SelectMainWeapon(TSubclassOf<ABaseWeapon> MainWeaponClass)
{
	AFPSWeaponLogicController* CurrentController = GetFPSUILogicController();
	if (CurrentController)
	{
		CurrentController->SetMainWeaponClass(MainWeaponClass);
		CurrentController->SpawnWeaponAndEquipToMain(MainWeaponClass);
	}
}

void UWeaponSelectUserWidget::SelectSubWeapon(TSubclassOf<ABaseWeapon> SubWeaponClass)
{
	AFPSWeaponLogicController* CurrentController = GetFPSUILogicController();
	if (CurrentController)
	{
		CurrentController->SetSubWeaponClass(SubWeaponClass);
		CurrentController->SpawnWeaponAndEquipToSub(SubWeaponClass);
	}
}

void UWeaponSelectUserWidget::SelectLethal(TSubclassOf<ABaseProjectile> LethalClass, UTexture2D* ProjectileTexture)
{
	AFPSUILogicController* CurrentController = GetFPSUILogicController();
	if (CurrentController)
	{
		CurrentController->SetLethalClass(LethalClass);
		CurrentController->SetLethalImage(ProjectileTexture);
		CurrentController->SetLethalCount(1);
	}
}

void UWeaponSelectUserWidget::SelectTactical(TSubclassOf<ABaseProjectile> TacticalClass, UTexture2D* ProjectileTexture)
{
	AFPSUILogicController* CurrentController = GetFPSUILogicController();
	if (CurrentController)
	{
		CurrentController->SetTacticalClass(TacticalClass);
		CurrentController->SetTacticalImage(ProjectileTexture);
		CurrentController->SetTacticalCount(1);
	}
}

void UWeaponSelectUserWidget::SelectCompleteButtonClick()
{
	AFPSUILogicController* CurrentController = GetFPSUILogicController();
	if (CurrentController)
	{
		CurrentController->ClientCloseWeaponSelectUI();
		CurrentController->SetShowMouseCursor(false);
	}
}
