// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WeaponStruct.generated.h"

class ABaseWeapon;
class ABaseProjectile;
/**
 * 
 */
USTRUCT(Atomic, BlueprintType)
struct BATTLEROYAL_API FWeaponData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> WeaponIcon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<USoundBase> Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BulletSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HeadDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BodyDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ArmDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HandDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LegDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FootDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RPM;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RecoilMultiply;
};

USTRUCT(Atomic, BlueprintType)
struct BATTLEROYAL_API FProjectileData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ProjectileName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> ProjectileIcon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<USoundBase> Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileArea;
	
};

class BATTLEROYAL_API WeaponStruct
{
public:
	WeaponStruct();
	~WeaponStruct();
};
