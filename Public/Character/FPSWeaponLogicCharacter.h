// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/FPSMovementLogicCharacter.h"
#include "Struct/PlayerStruct.h"
#include "FPSWeaponLogicCharacter.generated.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(LOG_FPSWeaponLogicCharacter, Log, All);

class ABaseWeapon;

UCLASS()
class BATTLEROYAL_API AFPSWeaponLogicCharacter : public AFPSMovementLogicCharacter
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
public:
	
	// --------------------------------- 플레이어 공격 관련 ------------------------------
	/**
	 * \brief 플레이어가 공격 버튼(마우스 좌클릭)을 눌렀을 때 실행화는 함수 \n
	 * 현재 들고 있는 무기의 종류를 확인하고 무기에 맞는 공격을 함 
	 *  
	 */
	UFUNCTION(Server, Reliable, Category = "Weapon")
	void ServerAttack();

protected:
	/**
	 * \brief 서버에서 총알을 발사하는 함수
	 */
	UFUNCTION(Server, Reliable, Category = "Weapon")
	void ServerFire();

	/**
	 * \brief 절차적 반동, 총구 화염, 발포 소리 재생, 수직반동을 재생하는 함수
	 */
	UFUNCTION(NetMulticast, Reliable, Category = "Weapon")
	void MultiFire(float RandomRecoilRotateRoll, float RandomRecoilRotatePitch, float RandomRecoilRotateYaw, float RandomRecoilVectorX, float RandomRecoilVectorY, float RandomRecoilVectorZ);

	/**
	 * \brief ServerFunction 공격을 멈추는 함수
	 */
	UFUNCTION(Server, Reliable, Category = "Weapon")
	void ServerStopAttack();

	/**
	 * \brief MultiFunction 공격을 멈추는 함수
	 */
	UFUNCTION(NetMulticast, Reliable, Category = "Weapon")
	void MultiStopAttack();

	/**
	 * \brief 공격 가능으로 변경하는 함수
	 */
	void CanFire();
		
public:
	/***/
	UFUNCTION(Server, Reliable, Category = "Weapon")
	void ServerStopRecoil();

protected:
	/**
	 * \brief 연사를 멈추기 위해 제작된 함수
	 */
	UFUNCTION(NetMulticast, Reliable, Category = "Weapon")
	void MultiStopRecoil();
	// --------------------------------- 플레이어 공격 관련 End ---------------------------

public:
	// --------------------------------- 조준 관련 --------------------------------------
	/**
	 * \brief 조준
	 */
	UFUNCTION()
	void Aiming();

	/**
	 * \brief 조준 해제
	 */
	UFUNCTION()
	void NonAiming();

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Weapon")
	void ServerSetbIsAiming(bool NewbIsAiming);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "Weapon")
	void MultiSetbIsAiming(bool NewbIsAiming);
	// --------------------------------- 조준 관련 End ----------------------------------

	// --------------------------------- 재장전 관련 ------------------------------------
	UFUNCTION(Server, Reliable, Category = "Weapon")
	void ServerTryReload();
	
	UFUNCTION(NetMulticast, Reliable, Category = "Weapon")
	void MultiTryReload();
	
	UFUNCTION(Category = "Weapon")
	void TryReload();

	UFUNCTION()
	void ReloadAmmo();
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool GetCanAttack();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetCanAttack(bool NewbCanAttack);

	UFUNCTION(Client, Reliable)
	void ClientHitDamage(AFPSBaseCharacter* Attacker);

	
	// --------------------------------- 재장전 관련 End --------------------------------

	// --------------------------------- IK 및 에임 관련 --------------------------------
	/**
	 * \brief 왼손 IK가 이루어질 지점을 반환하는 함수
	 * \return 왼손 IK Transform
	 */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FTransform GetLeftHandIKTransform();

	/**
	 * \brief 왼손 IK를 사용할지 여부를 반환하는 함수
	 * \return 왼손 IK 사용 bool값
	 */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool GetUseLeftHandIK();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetUseLeftHandIK(bool NewbUseLeftHandIK);
	/**
	 * \brief 
	 * \return 
	 */
	FRotator GetAimRotator();
	
	// --------------------------------- IK 및 에임 관련 End ----------------------------

	// --------------------------------- 총기 변경 -------------------------------------
	UFUNCTION(Server, Reliable, Category = "Weapon")
	void ServerChangeWeaponToMainWeapon();
	
	UFUNCTION(NetMulticast, Reliable, Category = "Weapon")
	void MultiChangeWeaponToMainWeapon();
	
	UFUNCTION(Category = "Weapon")
	void ChangeWeaponToMainWeapon();
	
	UFUNCTION(Server, Reliable, Category = "Weapon")
	void ServerChangeWeaponToSubWeapon();
	
	UFUNCTION(NetMulticast, Reliable, Category = "Weapon")
	void MultiChangeWeaponToSubWeapon();
	
	UFUNCTION(Category = "Weapon")
	void ChangeWeaponToSubWeapon();
	
	// --------------------------------- 총기 변경 End ---------------------------------

	/**
	 * \brief ChangeShotType
	 */
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Weapon")
	void ServerChangeShotType();
	
	UFUNCTION(BlueprintCallable)
	void SetAimCameraToWeaponCamera();

	UFUNCTION()
	void CurrentWeaponHidden(bool NewHidden);
public:
	/**
	 * \brief 플레이어가 현재 들고 있는 무기
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Weapon")
	ABaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Weapon")
	ABaseWeapon* MainWeapon = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Weapon")
	ABaseWeapon* SubWeapon = nullptr;

	/**
	 * \brief 플레이어가 들고 있는 무기의 종류
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Weapon")
	EEquipWeaponType PlayerEquipWeaponType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Weapon")
	FCarryAmmo CharacterCarryAmmo = FCarryAmmo();

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = "Weapon")
	bool bIsAttacking = false;
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Weapon")
	bool bCanAttack = true;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Weapon")
	bool bIsWeaponEquip = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Weapon")
	bool bIsNotFireDelay = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	int ShotCount = 0;

	FTimerHandle AutoFireTimerHandle;
	FTimerHandle ThreeTabFireTimerHandle;
	FTimerHandle TwoTabFireHandle;

	// --------- Recoil 관련 --------------------------------------------------
	FTimerHandle RecoilTimer;

	float RandomRecoilRotateRollMin = -5.0f;
	float RandomRecoilRotateRollMax = -2.5f;
	float RandomRecoilRotateYawMin = -0.16f;
	float RandomRecoilRotateYawMax = 0.16f;
	float RandomRecoilRotatePitchMin = -0.8f;
	float RandomRecoilRotatePitchMax = 0.8f;

	float RandomRecoilLocationXMin = -0.16f;
	float RandomRecoilLocationXMax = 0.16f;
	float RandomRecoilLocationYMin = -2.1f;
	float RandomRecoilLocationYMax = -1.1f;
	float RandomRecoilLocationZMin = -0.f;
	float RandomRecoilLocationZMax = 0.f;
	// --------- Recoil 관련 End ----------------------------------------------

	// --------- Montage ------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* UpperBodyMontage;
	// --------- Montage End --------------------------------------------------

	// --------- MeleeAttack ------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float MeleeAttackMontagePlayRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName MeleeAttackSectionName = FName(TEXT("MeleeAttack"));
	// --------- Sliding End --------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Weapon")
	bool bUseLeftHandIK = true;
	
	UPROPERTY(Replicated)
	int32 RandomSeed;
};
