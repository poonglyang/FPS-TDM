// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/FPSBaseAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "Character/FPSActionLogicCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UFPSBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerCharacter = Cast<AFPSActionLogicCharacter>(TryGetPawnOwner());
}

void UFPSBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!OwnerCharacter)
		return;

	DeltaTime = DeltaSeconds;

	bIsFalling = OwnerCharacter->GetCharacterMovement()->IsFalling();
	
	ForwardVelocity = UKismetMathLibrary::VSize(OwnerCharacter->GetVelocity());

	Direction = CalculateDirection(OwnerCharacter->GetCharacterMovement()->Velocity, OwnerCharacter->GetActorRotation());

	FRotator ClampRotator =
				UKismetMathLibrary::RInterpTo(FRotator(AimPitch, AimYaw, 0), OwnerCharacter->RotateDelta, DeltaSeconds, AimInterpSpeed);

	AimPitch = UKismetMathLibrary::ClampAngle(ClampRotator.Pitch, -90, 90);
	AimYaw = UKismetMathLibrary::ClampAngle(ClampRotator.Yaw, -90, 90);	

	AimRotation = OwnerCharacter->GetAimRotator();
	
	CharacterStance = OwnerCharacter->PlayerStance;
	
	EquipType = OwnerCharacter->PlayerEquipWeaponType;

	LeftHandIKSocketTransform = OwnerCharacter->GetLeftHandIKTransform();

	bUseLeftHandIK = OwnerCharacter->GetUseLeftHandIK();

	Recoil = UKismetMathLibrary::TInterpTo(Recoil, RecoilTransform, DeltaSeconds, RecoilInterpSpeed);

	RecoilTransform = UKismetMathLibrary::TInterpTo(RecoilTransform, FTransform(), DeltaSeconds, RecoilTransformInterpSpeed);

	bIsAttacking = OwnerCharacter->bIsAttacking;
}

void UFPSBaseAnimInstance::ProceduralRecoil(
	FRotator RandomRecoilRotate, FVector RandomRecoilLocation)
{
	RecoilTransform = FTransform(RandomRecoilRotate, RandomRecoilLocation);
}
