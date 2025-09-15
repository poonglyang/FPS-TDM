// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/FPSBaseCharacter.h"
#include "FPSMovementLogicCharacter.generated.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(LOG_FPSMovementLogicCharacter, Log, All);

UCLASS()
class BATTLEROYAL_API AFPSMovementLogicCharacter : public AFPSBaseCharacter
{
	GENERATED_BODY()


public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void Turn(const float AxisValue);

	void LookUp(const float AxisValue);

	/**
	 * \brief ServerFunction Change RotateDelta
	 * \param NewRotateDelta New RotateDelta Value
	 */
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Movement")
	void ServerSetRotateDelta(const FRotator NewRotateDelta);
	
	/**
	 * \brief Get PlayerRotator Yaw
	 * \return FRotator(0, PlayerController Rotator Yaw, 0);
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Movement")
	FRotator GetControlRotateZ();

	/**
	 * \brief Player move forward or backward 
	 * \param AxisValue input scale
	 */
	void MoveForwardBack(const float AxisValue);

	/**
	 * \brief Player move Right or Left 
	 * \param AxisValue input scale
	 */
	void MoveLeftRight(const float AxisValue);

	/**
	 * \brief ServerFunction Change LeftRightAxisValue
	 * \param AxisValue New LeftRightAxisValue Value
	 */
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Movement")
	void ServerSetLeftRightAxisValue(const float AxisValue);

	/**
	 * \brief if PlayerStance == Stand player jump else change PlayerStance to Stand
	 */
	void JumpStart();

	/**
	 * \brief stop jump
	 */
	void JumpStop();

	// -------------------------- Speed Change --------------------------------------
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Movement")
	void ServerSpeedChange();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, Category = "Movement")
	void MultiSpeedChange();
	
	/**
	 * \brief Change Movement MaxWalkSpeed
	 */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void ChangeSpeed();
	// -------------------------- Speed Change End-----------------------------------
	
	// -------------------------- RUN -------------------------
	UFUNCTION(Server, Reliable)
	void ServerStartRun();

	UFUNCTION(NetMulticast, Reliable)
	void MultiStartRun();

	UFUNCTION(Server, Reliable)
	void ServerStopRun();

	UFUNCTION(NetMulticast, Reliable)
	void MultiStopRun();
	// -------------------------- RUN End -------------------------

	// -------------------------- Capsule Change ------------------

	/**
	 * \brief translation z offset of mesh.
	 * \param Offset New translation z offset
	 */
	UFUNCTION(BlueprintCallable)
	void SetBaseTranslationOffsetZ(float Offset);
	
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Movement")
	void ServerSetCollisionAndMesh();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, Category = "Movement")
	void MultiSetCollisionAndMesh();

	/**
	 * \brief Change Collision And Mesh by PlayerStance
	 */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetCollisionAndMesh();
	// -------------------------- Capsule Change End---------------
	
	
	// -------------------------- Crouch --------------------------
	/**
	 * \brief Server Function Crouch
	 */
	UFUNCTION(Server, Reliable)
	void ServerCrouch();

	UFUNCTION(NetMulticast, Reliable)
	void MultiCrouch();

	UFUNCTION(BlueprintCallable)
	void NewCrouch();

	UFUNCTION(Server, Reliable)
	void ServerSliding();

	UFUNCTION(NetMulticast, Reliable)
	void MultiSliding();

	/**
	 * \brief Sliding
	 */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Sliding();
	
	// -------------------------- Crouch End ----------------------
	// -------------------------- Prone ---------------------------
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Movement")
	void ServerProne();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, Category = "Movement")
	void MultiProne();

	/**
	 * \brief Prone
	 */
	UFUNCTION(BlueprintCallable,  Category = "Movement")
	void Prone();
	// -------------------------- Prone End -----------------------
public:
	/**
	 * \brief Player RotateDelta
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Movement")
	FRotator RotateDelta = FRotator::ZeroRotator;
	
	/**
	 * \brief Player Input MoveRightAxisValue
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Movement")
	float LeftRightAxisValue = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerState")
	bool bIsRun = false;

	// --------- Player Move Speed ----------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StandAimingSpeed = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CrouchAimingSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float ProneAimingSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StandRunSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StandWalkSpeed = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CrouchSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float ProneSpeed = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SlidingSpeed = 450.f;
	// --------- Player Move Speed End ------------------------------------------

	// --------- PlayerStance Capsule Half Height --------------------------------
	/**
	 * \brief If PlayerStance is Stand Capsule's Half Height
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerState")
	float StandStanceHalfHeight = 88.0f;

	/**
	 * \brief If PlayerStance is Crouch Capsule's Half Height
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerState")
	float CrouchStanceHalfHeight = 44.0f;

	/**
	 * \brief If PlayerStance is Prone Capsule's Half Height
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerState")
	float ProneStanceHalfHeight = 18.0f;
	// --------- PlayerStance Capsule Half Height End-----------------------------

	// --------- PlayerStance Mesh Relative Location --------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerState")
	FVector StandStanceMeshRelativeLocation = FVector(0.0f, 0.0f, -90.f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerState")
	FVector CrouchStanceMeshRelativeLocation = FVector(0.0f, 0.0f, -44.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerState")
	FVector ProneStanceMeshRelativeLocation = FVector(0.0f, 0.0f, -18.f);
	// --------- PlayerStance Mesh Relative Location End-----------------------------

	// --------- PlayerStance Translation Offset Z-----------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerState")
	float StandTranslationOffsetZ = -90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerState")
	float CrouchTranslationOffsetZ = -44.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerState")
	float ProneTranslationOffsetZ = -18.f;
	// --------- PlayerStance Translation Offset Z End-------------------------

	// --------- Montage ------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* LowerBodyMontage;
	// --------- Montage End --------------------------------------------------

	// --------- Sliding ------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SlidingMontagePlayRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FName SlidingSectionName = FName(TEXT("Sliding2"));
	// --------- Sliding End --------------------------------------------------


	
};


