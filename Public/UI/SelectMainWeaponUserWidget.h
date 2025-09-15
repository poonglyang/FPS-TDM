// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectMainWeaponUserWidget.generated.h"

class UDataTable;
class ABaseWeapon;
class UWeaponSelectButtonUserWidget;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMainWeaponSelectButtonClick, TSubclassOf<ABaseWeapon>, WeaponClass);

DECLARE_LOG_CATEGORY_EXTERN(LOG_SelectMainWeaponUserWidget, Log, All);

class UScrollBox;

UCLASS()
class BATTLEROYAL_API USelectMainWeaponUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	USelectMainWeaponUserWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativePreConstruct() override;

	virtual void InitScrollBox(UScrollBox* WeaponSelectScrollBox, UDataTable* WeaponDataTable);

	UFUNCTION()
	virtual void WeaponButtonClick(TSubclassOf<ABaseWeapon> WeaponClass);

public:
	UPROPERTY()
	FOnMainWeaponSelectButtonClick OnMainWeaponSelectButtonClick; 
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SelectMainWeapon")
	TSubclassOf<UWeaponSelectButtonUserWidget> ButtonWidgetClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* LMGScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* SMGScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* ARScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* SRScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* ShotgunScrollBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SelectMainWeapon")
	UDataTable* LMGDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SelectMainWeapon")
	UDataTable* SMGDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SelectMainWeapon")
	UDataTable* ARDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SelectMainWeapon")
	UDataTable* SRDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SelectMainWeapon")
	UDataTable* ShotgunDataTable;

	
};
