// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SelectSubWeaponUserWidget.h"

#include "Components/ScrollBox.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Engine/DataTable.h"
#include "Struct/WeaponStruct.h"
#include "UI/WeaponSelectButtonUserWidget.h"

DEFINE_LOG_CATEGORY(LOG_SelectSubWeaponUserWidget);

USelectSubWeaponUserWidget::USelectSubWeaponUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> PistolDataTableObject(TEXT("/Game/Blueprint/Table/CPPTable/DT_Pistol.DT_Pistol"));
	if (PistolDataTableObject.Succeeded()) {
		PistolDataTable = PistolDataTableObject.Object;
	}
	else {
		UE_LOG(LOG_SelectSubWeaponUserWidget, Error, TEXT("PistolDataTable Call Fail"));
	}
	
	static ConstructorHelpers::FObjectFinder<UDataTable> LethalDataTableObject(TEXT("/Game/Blueprint/Table/CPPTable/DT_Lethal.DT_Lethal"));
	if (LethalDataTableObject.Succeeded()) {
		LethalDataTable = LethalDataTableObject.Object;
	}
	else {
		UE_LOG(LOG_SelectSubWeaponUserWidget, Error, TEXT("LethalDataTable Call Fail"));
	}
	

	static ConstructorHelpers::FObjectFinder<UDataTable> TacticalDataTableObject(TEXT("/Game/Blueprint/Table/CPPTable/DT_Tactical.DT_Tactical"));
	if (TacticalDataTableObject.Succeeded()) {
		TacticalDataTable = TacticalDataTableObject.Object;
	}
	else {
		UE_LOG(LOG_SelectSubWeaponUserWidget, Error, TEXT("TacticalDataTable Call Fail"));
	}
	
}

void USelectSubWeaponUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!ButtonWidgetClass)
		return;
	
	if (PistolUniformGridPanel && PistolDataTable)
	{
		TArray<FName> PistolNames = PistolDataTable->GetRowNames();
		for (int i = 0; i < PistolNames.Num(); i++)
		{
			FWeaponData* Row = PistolDataTable->FindRow<FWeaponData>(PistolNames[i], TEXT("General"));

			if (!Row)
				continue;

			UWeaponSelectButtonUserWidget* CurrentButton = Cast<UWeaponSelectButtonUserWidget>(CreateWidget<UWeaponSelectButtonUserWidget>(GetOwningPlayer(), ButtonWidgetClass));

			if (!CurrentButton)
				continue;

			CurrentButton->InitButton(Row->WeaponIcon.Get(), Row->WeaponName, Row->WeaponClass);
			CurrentButton->OnButtonWeaponSelectButtonClick.AddDynamic(this , &USelectSubWeaponUserWidget::WeaponButtonClick);
			
			UUniformGridSlot* GridSlot = PistolUniformGridPanel->AddChildToUniformGrid(CurrentButton, i / UniformGridPanelCol, i % UniformGridPanelCol);

			if (GridSlot)
			{
				GridSlot->SetHorizontalAlignment(HAlign_Center);
				GridSlot->SetVerticalAlignment(VAlign_Center);
			}

			
		}
	}
		
	if (LethalScrollBox && LethalDataTable)
	{
		TArray<FName> LethalNames = LethalDataTable->GetRowNames();
		for (FName RowName : LethalNames)
		{
			FProjectileData* Row = LethalDataTable->FindRow<FProjectileData>(RowName, TEXT("General"));

			if (!Row)
				continue;
				
			UWeaponSelectButtonUserWidget* CurrentButton = Cast<UWeaponSelectButtonUserWidget>(CreateWidget<UWeaponSelectButtonUserWidget>(GetOwningPlayer(), ButtonWidgetClass));

			if (!CurrentButton)
				continue;

			CurrentButton->InitButton(Row->ProjectileIcon.Get(), Row->ProjectileName, Row->ProjectileClass);
			CurrentButton->OnButtonProjectileSelectButtonClick.AddDynamic(this , &USelectSubWeaponUserWidget::LethalButtonClick);

			LethalScrollBox->AddChild(CurrentButton);
		}
	}
		
	
	if (TacticalScrollBox && TacticalDataTable)
	{
		TArray<FName> TacticalNames = TacticalDataTable->GetRowNames();
		for (FName RowName : TacticalNames)
		{
			FProjectileData* Row = TacticalDataTable->FindRow<FProjectileData>(RowName, TEXT("General"));

			if (!Row)
				continue;
				
			UWeaponSelectButtonUserWidget* CurrentButton = Cast<UWeaponSelectButtonUserWidget>(CreateWidget<UWeaponSelectButtonUserWidget>(GetOwningPlayer(), ButtonWidgetClass));

			if (!CurrentButton)
				continue;

			CurrentButton->InitButton(Row->ProjectileIcon.Get(), Row->ProjectileName, Row->ProjectileClass);
			CurrentButton->OnButtonProjectileSelectButtonClick.AddDynamic(this , &USelectSubWeaponUserWidget::TacticalButtonClick);

			TacticalScrollBox->AddChild(CurrentButton);
		}
	}
}

void USelectSubWeaponUserWidget::InitScrollBox(UScrollBox* WeaponSelectScrollBox, UDataTable* WeaponDataTable)
{
	if (!WeaponSelectScrollBox || !WeaponDataTable)
		return;
	
	if (WeaponDataTable)
	{
		
	}
}

void USelectSubWeaponUserWidget::WeaponButtonClick(TSubclassOf<ABaseWeapon> WeaponClass)
{
	OnSubWeaponSelectButtonClick.Broadcast(WeaponClass);
}

void USelectSubWeaponUserWidget::LethalButtonClick(TSubclassOf<ABaseProjectile> ProjectileClass, UTexture2D* ProjectileTexture)
{
	OnLethalSelectButtonClick.Broadcast(ProjectileClass, ProjectileTexture);
}

void USelectSubWeaponUserWidget::TacticalButtonClick(TSubclassOf<ABaseProjectile> ProjectileClass, UTexture2D* ProjectileTexture)
{
	OnTacticalSelectButtonClick.Broadcast(ProjectileClass, ProjectileTexture);
}
