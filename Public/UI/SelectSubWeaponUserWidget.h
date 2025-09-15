// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SelectSubWeaponUserWidget.generated.h"

class ABaseProjectile;
class UUniformGridPanel;
class UScrollBox;
class UTexture2D;
class UDataTable;
class UWeaponSelectButtonUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSubWeaponSelectButtonClick, TSubclassOf<ABaseWeapon>, WeaponClass);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLethalSelectButtonClick, TSubclassOf<ABaseProjectile>, ProjectileClass, UTexture2D*, ProjectileTexture);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTacticalSelectButtonClick, TSubclassOf<ABaseProjectile>, ProjectileClass, UTexture2D*, ProjectileTexture);

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(LOG_SelectSubWeaponUserWidget, Log, All);

UCLASS()
class BATTLEROYAL_API USelectSubWeaponUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	USelectSubWeaponUserWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativePreConstruct() override;

	virtual void InitScrollBox(UScrollBox* WeaponSelectScrollBox, UDataTable* WeaponDataTable);

	UFUNCTION()
	virtual void WeaponButtonClick(TSubclassOf<ABaseWeapon> WeaponClass);

	UFUNCTION()
	virtual void LethalButtonClick(TSubclassOf<ABaseProjectile> ProjectileClass, UTexture2D* ProjectileTexture);

	UFUNCTION()
	virtual void TacticalButtonClick(TSubclassOf<ABaseProjectile> ProjectileClass, UTexture2D* ProjectileTexture);
	
public:
	FOnSubWeaponSelectButtonClick OnSubWeaponSelectButtonClick;
	FOnLethalSelectButtonClick OnLethalSelectButtonClick;
	FOnTacticalSelectButtonClick OnTacticalSelectButtonClick;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SelectMainWeapon")
	TSubclassOf<UWeaponSelectButtonUserWidget> ButtonWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SelectMainWeapon")
	int UniformGridPanelCol = 2;
	
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* PistolUniformGridPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* LethalScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* TacticalScrollBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SelectMainWeapon")
	UDataTable* PistolDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SelectMainWeapon")
	UDataTable* TacticalDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SelectMainWeapon")
	UDataTable* LethalDataTable;
};
