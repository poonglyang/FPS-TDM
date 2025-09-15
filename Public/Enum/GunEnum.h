// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunEnum.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Pistol UMETA(DisplayName="Pistol"),
	AR UMETA(DisplayName="AR"),
	SMG UMETA(DisplayName="SMG"),
	LMG UMETA(DisplayName="LMG"),
	Shotgun UMETA(DisplayName="Shotgun"),
	Sniper UMETA(DisplayName="Sniper"),
	Rocket UMETA(DisplayName="Rocket")
};

UENUM(BlueprintType)
enum class EShotType : uint8
{
	/**
	 * \brief Semi-Auto Mode
	 */
	SemiAuto UMETA(DisplayName = "Semi-Auto"),

	/**
	 * \brief Auto Mode
	 */
	Auto UMETA(DisplayName = "Auto"),

	/**
	 * \brief ThreeTabBurst Mode
	 */
	ThreeTabBurst UMETA(DisplayName = "ThreeTabBurst"),

	/**
	 * \brief TwoTabBurst Mode
	 */
	TwoTabBurst UMETA(DisplayName = "TwoTabBurst")
};

class BATTLEROYAL_API GunEnum
{
public:
	GunEnum();
	~GunEnum();
};
