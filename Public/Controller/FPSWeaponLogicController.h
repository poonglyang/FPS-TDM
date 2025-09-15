// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/FPSMovementLogicController.h"
#include "FPSWeaponLogicController.generated.h"

class ABaseProjectile;
class ABaseWeapon;
/**
 * 
 */
class AFPSWeaponLogicCharacter;

UCLASS()
class BATTLEROYAL_API AFPSWeaponLogicController : public AFPSMovementLogicController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	AFPSWeaponLogicCharacter* GetWeaponLogicCharacter() const;
	
	//------------------- 공격 ------------------------
	UFUNCTION()
	virtual void AttackPressed();

	UFUNCTION()
	virtual void AttackReleased();
	//------------------- 공격 End --------------------

	//------------------- 조준 ------------------------
	UFUNCTION()
	virtual void AimingPressed();

	UFUNCTION()
	virtual void AimingReleased();
	//------------------- 조준 End --------------------
	
	/**
	 * \brief 재장전
	 */
	UFUNCTION()
	virtual void Reload();

	/**
	 * 메인 무기 변경
	 */
	UFUNCTION()
	virtual void ChangeWeaponToMainWeapon();

	/**
	 * 서브 무기 변경
	 */
	UFUNCTION()
	virtual void ChangeWeaponToSubWeapon();

	/**
	 * \brief 총의 사격 방식 변경
	 */
	UFUNCTION()
	virtual void ChangeShotType();

public:
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Weapon Logic Controller")
	void SetMainWeaponClass(TSubclassOf<ABaseWeapon> NewMainWeaponClass);

	TSubclassOf<ABaseWeapon> GetMainWeaponClass() const;

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Weapon Logic Controller")
	void SetSubWeaponClass(TSubclassOf<ABaseWeapon> NewSubWeaponClass);

	TSubclassOf<ABaseWeapon> GetSubWeaponClass() const;

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Weapon Logic Controller")
	void SetLethalClass(TSubclassOf<ABaseProjectile> NewLethalClass);

	TSubclassOf<ABaseProjectile> GetLethalClass() const;

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Weapon Logic Controller")
	void SetTacticalClass(TSubclassOf<ABaseProjectile> NewTacticalClass);

	TSubclassOf<ABaseProjectile> GetTacticalClass() const;

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Weapon Logic Controller")
	void SpawnWeaponAndEquipToMain(TSubclassOf<ABaseWeapon> TargetWeaponClass);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Weapon Logic Controller")
	void SpawnWeaponAndEquipToSub(TSubclassOf<ABaseWeapon> TargetWeaponClass);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Weapon Logic Controller")
	TSubclassOf<ABaseWeapon> MainWeaponClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Weapon Logic Controller")
	TSubclassOf<ABaseWeapon> SubWeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Weapon Logic Controller")
	TSubclassOf<ABaseProjectile> LethalClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Weapon Logic Controller")
	TSubclassOf<ABaseProjectile> TacticalClass;
};

