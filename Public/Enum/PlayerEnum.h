// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EEquipWeaponType : uint8
{
	/**
	 * \brief Equip Nothing
	 */
	None UMETA(DisplayName = "None"),

	/**
	 * \brief Equip Melee
	 */
	Melee UMETA(DisplayName = "Melee"),

	/**
	 * \brief Equip AR
	 */
	AR UMETA(DisplayName = "AR"),
	
	/**
	 * \brief Equip AR
	 */
	Pistol UMETA(DisplayName = "Pistol"),
};

UENUM(BlueprintType)
enum class EPlayerStanceMode : uint8
{
	/**
	 * \brief Stand Mode
	 */
	Stand UMETA(DisplayName = "Stand"),

	/**
	 * \brief Crouch Mode
	 */
	Crouch UMETA(DisplayName = "Crouch"),

	/**
	 * \brief Prone Mode
	 */
	Prone UMETA(DisplayName = "Prone"),
};

class BATTLEROYAL_API PlayerEnum
{
public:
	PlayerEnum();
	~PlayerEnum();
};
