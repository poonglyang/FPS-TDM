// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enum/GunEnum.h"
#include "Enum/PlayerEnum.h"
#include "BaseWeapon.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LOG_BaseWeapon, Log, All);

class UCapsuleComponent;
class USceneComponent;
class UNiagaraSystem;
class USoundBase;
class UTexture2D;
class ABaseBullet;
class UDataTable;

UCLASS()
class BATTLEROYAL_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	virtual void OnRep_CurrentAmmo();

public:
	/**
	 * \brief 총알 발싸
	 */
	virtual void FireBullet();

	/**
	 * \brief 총구 화염 VFX 실행
	 */
	virtual void MuzzleFlash();

	/**
	 * \brief 사격 소리 재생
	 */
	virtual void PlayFireSound();

	/**
	 * \brief 현재 총에 남아있는 총알을 반환하는 함수
	 * \return 현재 총에 남아있는 총알
	 */
	int GetCurrentAmmoCount() const;

	/**
	 * \brief 총기의 최대 탄창 크기를 반환하는 함수
	 * \return 총기의 탄창 크기
	 */
	int GetMaxAmmoCount() const;

	/**
	 * \brief 왼손 IK 위치를 반환하는 함수
	 * \return 왼손 IK 위치
	 */
	FTransform GetLeftHandIKTransform() const;

	/**
	 * \brief 오른손 위치(장착했을 시의)를 반환하는 함수
	 * \return 오른손 위치
	 */
	FTransform GetRightHandTransform() const;

	/**
	 * \brief NewAmmo만큼 재장전 하는 함수
	 * \param NewAmmo 재장전할 총알 개수
	 */
	UFUNCTION(BlueprintCallable)
	virtual void Reload(int NewAmmo);

	/**
	 * \brief 사격 방식을 바꾸는 함수
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ChangeShotType();
	virtual void ChangeShotType_Implementation();

	/**
	 * \brief 총기의 아이콘(Texture2D)를 반환하는 함수
	 * \return 총기의 아이콘
	 */
	UFUNCTION(BlueprintCallable)
	UTexture2D* GetIcon() const;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "SpawnBullet")
	void SpawnBullet();
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	USceneComponent* DefaultSceneRoot;
	
	/**
	 * \brief 총기의 상호작용 용 콜리전
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	UCapsuleComponent* InteractionCapsuleCollision;

	/**
	 * \brief 카메라가 위치할 위치
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	USceneComponent* AimCameraLoc;

	/**
	 * \brief 총구 위치
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	USceneComponent* ShotPoint;

	/**
	 * \brief 장비 팔 타입
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	EEquipWeaponType WeaponEquipType;

	/**
	 * \brief 총기 종류
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	EWeaponType WeaponType;

	/**
	 * \brief 사격 종류
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated,  Category = "Weapon")
	EShotType ShotType;

	/**
	 * \brief 연사 속도
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	float Rpm;

	/**
	 * \brief 반동(이다)
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	float RecoilMultiply = 1.f;

	/**
	 * \brief 현재 총에 남아 있는 총알 개수
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, ReplicatedUsing=OnRep_CurrentAmmo, Category = "Weapon")
	int CurrentAmmo = 0;

	/**
	 * \brief 최대 탄창
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Weapon")
	int MaxAmmo = 0;

	/**
	 * \brief IK 소켓이 있는 컴포넌트
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	UStaticMeshComponent* IKSocketMesh;

	/**
	 * \brief 오른손 위치
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	FTransform RightHandTransform;

	/**
	 * \brief 삭제 타이머
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	FTimerHandle DestroyTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	UTexture2D* WeaponIcon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	USoundBase* FireSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	UNiagaraSystem* FireEffectMuzzle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnBullet")
	bool bSpawnBulletBP = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	TSubclassOf<ABaseBullet> BulletClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BulletSpeed")
	float BulletSpeed = 500000.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponDamage")
	float HeadDamage = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponDamage")
	float BodyDamage = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponDamage")
	float ArmDamage = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponDamage")
	float HandDamage = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponDamage")
	float LegDamage = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponDamage")
	float FootDamage = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ShotType")
	EShotType ShotTypeA;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ShotType")
	EShotType ShotTypeB;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponInit")
	UDataTable* WeaponDataTable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponInit")
	FName WeaponDTName;
};
