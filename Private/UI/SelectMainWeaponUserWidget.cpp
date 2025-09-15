// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SelectMainWeaponUserWidget.h"

#include "Components/ScrollBox.h"
#include "Engine/DataTable.h"
#include "Struct/WeaponStruct.h"
#include "UI/WeaponSelectButtonUserWidget.h"


DEFINE_LOG_CATEGORY(LOG_SelectMainWeaponUserWidget);

USelectMainWeaponUserWidget::USelectMainWeaponUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> LMGDataTableObject(TEXT("/Game/Blueprint/Table/CPPTable/DT_LMG.DT_LMG"));
	if (LMGDataTableObject.Succeeded()) {
		LMGDataTable = LMGDataTableObject.Object;
	}
	else {
		UE_LOG(LOG_SelectMainWeaponUserWidget, Error, TEXT("LMGDataTable Call Fail"));
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> SMGDataTableObject(TEXT("/Game/Blueprint/Table/CPPTable/DT_SMG.DT_SMG"));
	if (SMGDataTableObject.Succeeded()) {
		SMGDataTable = SMGDataTableObject.Object;
	}
	else {
		UE_LOG(LOG_SelectMainWeaponUserWidget, Error, TEXT("SMGDataTable Call Fail"));
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> ARDataTableObject(TEXT("/Game/Blueprint/Table/CPPTable/DT_AR.DT_AR"));
	if (ARDataTableObject.Succeeded()) {
		ARDataTable = ARDataTableObject.Object;
	}
	else {
		UE_LOG(LOG_SelectMainWeaponUserWidget, Error, TEXT("ARDataTable Call Fail"));
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> SniperDataTableObject(TEXT("/Game/Blueprint/Table/CPPTable/DT_SR.DT_SR"));
	if (SniperDataTableObject.Succeeded()) {
		SRDataTable = SniperDataTableObject.Object;
	}
	else {
		UE_LOG(LOG_SelectMainWeaponUserWidget, Error, TEXT("SRDataTable Call Fail"));
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> ShotgunDataTableObject(TEXT("/Game/Blueprint/Table/CPPTable/DT_Shotgun.DT_Shotgun"));
	if (ShotgunDataTableObject.Succeeded()) {
		ShotgunDataTable = ShotgunDataTableObject.Object;
	}
	else {
		UE_LOG(LOG_SelectMainWeaponUserWidget, Error, TEXT("ShotgunDataTable Call Fail"));
	}
}

void USelectMainWeaponUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!ButtonWidgetClass)
		return;

	if (LMGScrollBox && LMGDataTable)
		InitScrollBox(LMGScrollBox, LMGDataTable);

	if (SMGScrollBox && SMGDataTable)
		InitScrollBox(SMGScrollBox, SMGDataTable);

	if (ARScrollBox && ARDataTable)
		InitScrollBox(ARScrollBox, ARDataTable);

	if (SRScrollBox && SRDataTable)
		InitScrollBox(SRScrollBox, SRDataTable);

	if (ShotgunScrollBox && ShotgunDataTable)
		InitScrollBox(ShotgunScrollBox, ShotgunDataTable);

		
}

void USelectMainWeaponUserWidget::InitScrollBox(UScrollBox* WeaponSelectScrollBox, UDataTable* WeaponDataTable)
{
	if (!WeaponSelectScrollBox || !WeaponDataTable)
		return;
	
	if (WeaponDataTable)
	{
		TArray<FName> LMGNames = WeaponDataTable->GetRowNames();
		for (FName RowName : LMGNames)
		{
			FWeaponData* Row = WeaponDataTable->FindRow<FWeaponData>(RowName, TEXT("General"));

			if (!Row)
				continue;
			
			UWeaponSelectButtonUserWidget* CurrentButton = Cast<UWeaponSelectButtonUserWidget>(CreateWidget<UWeaponSelectButtonUserWidget>(GetOwningPlayer(), ButtonWidgetClass));

			if (!CurrentButton)
				continue;

			CurrentButton->InitButton(Row->WeaponIcon.Get(), Row->WeaponName, Row->WeaponClass);
			CurrentButton->OnButtonWeaponSelectButtonClick.AddDynamic(this , &USelectMainWeaponUserWidget::WeaponButtonClick);

			WeaponSelectScrollBox->AddChild(CurrentButton);
		}
	}
}

void USelectMainWeaponUserWidget::WeaponButtonClick(TSubclassOf<ABaseWeapon> WeaponClass)
{
	OnMainWeaponSelectButtonClick.Broadcast(WeaponClass);
}
