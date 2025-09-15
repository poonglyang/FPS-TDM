// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FPSMovementLogicCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Enum/PlayerEnum.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"


DEFINE_LOG_CATEGORY(LOG_FPSMovementLogicCharacter);

void AFPSMovementLogicCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSMovementLogicCharacter, LeftRightAxisValue, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSMovementLogicCharacter, RotateDelta, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSMovementLogicCharacter, bIsAiming, COND_None, REPNOTIFY_Always);
}

void AFPSMovementLogicCharacter::Turn(const float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AFPSMovementLogicCharacter::LookUp(const float AxisValue)
{
	AddControllerPitchInput(AxisValue);
	ServerSetRotateDelta(UKismetMathLibrary::NormalizedDeltaRotator(GetControlRotation(), GetActorRotation()));
}

void AFPSMovementLogicCharacter::ServerSetRotateDelta_Implementation(const FRotator NewRotateDelta)
{
	RotateDelta = NewRotateDelta;
}

FRotator AFPSMovementLogicCharacter::GetControlRotateZ()
{
	return FRotator(0, GetControlRotation().Yaw,0);
}

void AFPSMovementLogicCharacter::MoveForwardBack(const float AxisValue)
{
	AddMovementInput(UKismetMathLibrary::GetForwardVector(GetControlRotateZ()), AxisValue); 
}

void AFPSMovementLogicCharacter::MoveLeftRight(const float AxisValue)
{
	if (PlayerStance == EPlayerStanceMode::Prone)
	{
		if (!bIsAiming)
		{
			ServerSetLeftRightAxisValue(AxisValue);
			AddMovementInput(UKismetMathLibrary::GetRightVector(GetControlRotateZ()), AxisValue);
		}
		else
		{
			ServerSetLeftRightAxisValue(0);
		}
		
	}
	else
	{
		ServerSetLeftRightAxisValue(AxisValue);
		AddMovementInput(UKismetMathLibrary::GetRightVector(GetControlRotateZ()), AxisValue);
	}
}

void AFPSMovementLogicCharacter::ServerSetLeftRightAxisValue_Implementation(const float AxisValue)
{
	LeftRightAxisValue = AxisValue;
}

void AFPSMovementLogicCharacter::JumpStart()
{
	if (PlayerStance == EPlayerStanceMode::Stand)
		Jump();
	else
		ServerSetPlayerStance(EPlayerStanceMode::Stand);
}

void AFPSMovementLogicCharacter::JumpStop()
{
	StopJumping();
}

void AFPSMovementLogicCharacter::ServerSpeedChange_Implementation()
{
	MultiSpeedChange();
}

void AFPSMovementLogicCharacter::MultiSpeedChange_Implementation()
{
	ChangeSpeed();
}

void AFPSMovementLogicCharacter::ChangeSpeed()
{
	if (bIsAiming)
	{
		//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("에이밍")));
		// 조준 중일 때
		switch (PlayerStance) {
		case EPlayerStanceMode::Stand:
			
			GetCharacterMovement()->MaxWalkSpeed = StandAimingSpeed; 
			break;
		case EPlayerStanceMode::Crouch:
			GetCharacterMovement()->MaxWalkSpeed = CrouchAimingSpeed;
			break;
		case EPlayerStanceMode::Prone:
			GetCharacterMovement()->MaxWalkSpeed = ProneAimingSpeed;
			break;
		}
	}
	else
	{
		if (bIsRun)
		{
			// 달리기 중일 때
			switch (PlayerStance) {
			case EPlayerStanceMode::Stand:
				GetCharacterMovement()->MaxWalkSpeed = StandRunSpeed; 
				break;
			case EPlayerStanceMode::Crouch:
				GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
				break;
			case EPlayerStanceMode::Prone:
				GetCharacterMovement()->MaxWalkSpeed = ProneSpeed;
				break;
			}
		}
		else
		{
			// 달리기 중이 아닐 때
			switch (PlayerStance) {
			case EPlayerStanceMode::Stand:
				GetCharacterMovement()->MaxWalkSpeed = StandWalkSpeed; 
				break;
			case EPlayerStanceMode::Crouch:
				GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
				break;
			case EPlayerStanceMode::Prone:
				GetCharacterMovement()->MaxWalkSpeed = ProneSpeed;
				break;
			}
		}
	}
}

void AFPSMovementLogicCharacter::SetBaseTranslationOffsetZ(float Offset)
{
	BaseTranslationOffset.Z = Offset;
}

void AFPSMovementLogicCharacter::ServerSetCollisionAndMesh_Implementation()
{
	MultiSetCollisionAndMesh();
}

void AFPSMovementLogicCharacter::MultiSetCollisionAndMesh_Implementation()
{
	SetCollisionAndMesh();
}

void AFPSMovementLogicCharacter::SetCollisionAndMesh()
{
	switch (PlayerStance) {
	case EPlayerStanceMode::Stand:
		GetCapsuleComponent()->SetCapsuleHalfHeight(StandStanceHalfHeight);
		GetMesh()->SetRelativeLocation(StandStanceMeshRelativeLocation);
		SetBaseTranslationOffsetZ(StandTranslationOffsetZ);
		break;
	case EPlayerStanceMode::Crouch:
		GetCapsuleComponent()->SetCapsuleHalfHeight(CrouchStanceHalfHeight);
		GetMesh()->SetRelativeLocation(CrouchStanceMeshRelativeLocation);
		SetBaseTranslationOffsetZ(CrouchTranslationOffsetZ);
		break;
	case EPlayerStanceMode::Prone:
		GetCapsuleComponent()->SetCapsuleHalfHeight(ProneStanceHalfHeight);
		GetMesh()->SetRelativeLocation(ProneStanceMeshRelativeLocation);
		SetBaseTranslationOffsetZ(ProneTranslationOffsetZ);
		break;
	}

}



void AFPSMovementLogicCharacter::ServerStartRun_Implementation()
{
	MultiStartRun();
}

void AFPSMovementLogicCharacter::MultiStartRun_Implementation()
{
	bIsRun = true;
	ChangeSpeed();
}

void AFPSMovementLogicCharacter::ServerStopRun_Implementation()
{
	MultiStopRun();
}

void AFPSMovementLogicCharacter::MultiStopRun_Implementation()
{
	bIsRun = false;
	ChangeSpeed();
}

void AFPSMovementLogicCharacter::ServerCrouch_Implementation()
{
	MultiCrouch();
}

void AFPSMovementLogicCharacter::MultiCrouch_Implementation()
{
	NewCrouch();
}

void AFPSMovementLogicCharacter::NewCrouch()
{
	if (PlayerStance == EPlayerStanceMode::Crouch)
	{
		PlayerStance = EPlayerStanceMode::Stand;
	}
	else
	{
		PlayerStance = EPlayerStanceMode::Crouch;
		if (
			UKismetMathLibrary::VSize(GetCharacterMovement()->Velocity) > SlidingSpeed
			&& !GetCharacterMovement()->IsFalling()
		)
		{
			ServerSliding();
		}
	}

	ServerChangeCamera();
	ServerSpeedChange();
	ServerSetCollisionAndMesh();
}

void AFPSMovementLogicCharacter::ServerSliding_Implementation()
{
	MultiSliding();
}

void AFPSMovementLogicCharacter::MultiSliding_Implementation()
{
	Sliding();
}

void AFPSMovementLogicCharacter::Sliding()
{
	PlayMontageWithSession(LowerBodyMontage, SlidingSectionName, SlidingMontagePlayRate);
}

void AFPSMovementLogicCharacter::ServerProne_Implementation()
{
	MultiProne();
}

void AFPSMovementLogicCharacter::MultiProne_Implementation()
{
	Prone();
}

void AFPSMovementLogicCharacter::Prone()
{
	if (PlayerStance == EPlayerStanceMode::Prone)
	{
		PlayerStance = EPlayerStanceMode::Stand;
	}
	else
	{
		PlayerStance = EPlayerStanceMode::Prone;
	}

	ServerChangeCamera();
	ServerSpeedChange();
	ServerSetCollisionAndMesh();
	
}
