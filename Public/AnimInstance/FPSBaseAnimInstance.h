// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Enum/PlayerEnum.h"
#include "FPSBaseAnimInstance.generated.h"

class AFPSActionLogicCharacter;
/**
 * 
 */
UCLASS()
class BATTLEROYAL_API UFPSBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void ProceduralRecoil(FRotator RandomRecoilRotate, FVector RandomRecoilLocation);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	float DeltaTime;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	AFPSActionLogicCharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	bool bIsFalling;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	float ForwardVelocity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	float Direction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	float RightVelocity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	float AimPitch = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	float AimYaw = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	float AimInterpSpeed = 15.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	EPlayerStanceMode CharacterStance = EPlayerStanceMode::Stand;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	FRotator AimRotation;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	bool bUseLeftHandIK;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	FTransform LeftHandIKSocketTransform;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	FTransform Recoil = FTransform();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	FTransform RecoilTransform = FTransform();

	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	float RecoilInterpSpeed = 25.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	float RecoilTransformInterpSpeed = 15.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	EEquipWeaponType EquipType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	bool bIsDie = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimInstance")
	bool bIsAttacking = false;
	
};
