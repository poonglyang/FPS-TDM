// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enum/PlayerEnum.h"
#include "Struct/PlayerStruct.h"
#include "FPSBaseCharacter.generated.h"



DECLARE_LOG_CATEGORY_EXTERN(LOG_FPSBaseCharacter, Log, All);

class USpringArmComponent;
class UChildActorComponent;
class UFuckTestSkeletalMeshComponent;

UCLASS()
class BATTLEROYAL_API AFPSBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSBaseCharacter();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostInitializeComponents() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	/**
	 * \brief Set Master Pose To GetMesh()'s children Mesh
	 */
	UFUNCTION(BlueprintCallable, Category = "CharacterMesh")
	virtual void MasterPoseToChildrenMesh();


public:
	/**
	 * \brief ServerFunction Change PlayerStance to NewStance
	 * \param NewStance New PlayerStance Value
	 */
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Movement")
	void ServerSetPlayerStance(EPlayerStanceMode NewStance);
	
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Animation")
	void ServerChangeCamera();
	
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, Category = "Animation")
	void MultiChangeCamera();
	
	UFUNCTION(BlueprintCallable, Category = "CharacterMesh")
	void ChangeCamera();
	
	//------------------------ Montage -------------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Animation")
	void ServerMontagePlayWithSession(UAnimMontage* Montage, FName SectionName = FName(TEXT("")), float PlayRate = 1.f);

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, Category = "Animation")
	void MultiMontagePlayWithSession(UAnimMontage* Montage, FName SectionName = FName(TEXT("")), float PlayRate = 1.f);

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayMontageWithSession(UAnimMontage* Montage, FName SectionName = FName(TEXT("")), float PlayRate = 1.f);
	//------------------------ Montage End----------------------------------------------------------------------------

	UFUNCTION(Server, Reliable)
	void ServerStartHealthRegen(float HealDelay, float HealAmount);

	UFUNCTION()
	void HealthRegenStart(float HealAmount);

	UFUNCTION()
	void HealthRegen(float HealAmount);
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "PlayerState")
	FCharacterState CharacterState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "PlayerState", meta=(ExposeOnSpawn=true))
	bool bIsGamePlay = true;

	
	/**
	 * \brief Player Stance Enum (Stand, Crouch, Prone)
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "PlayerState")
	EPlayerStanceMode PlayerStance;
	
	// ----------------------- Mesh ----------------------------------------------
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterMesh")
	USkeletalMeshComponent* Head;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterMesh")
	USkeletalMeshComponent* UpperBody;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterMesh")
	USkeletalMeshComponent* Armor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterMesh")
	USkeletalMeshComponent* Clavicle;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterMesh")
	USkeletalMeshComponent* UpperArm;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterMesh")
	USkeletalMeshComponent* LowerArm;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterMesh")
	USkeletalMeshComponent* Hand;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterMesh")
	USkeletalMeshComponent* LowerBody;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterMesh")
	USkeletalMeshComponent* Foot;
	// ----------------------- Mesh End ------------------------------------------

	// ----------------------- Camera --------------------------------------------
	/**
	 * \brief 현재 플레이어의 카메라
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	UChildActorComponent* CurrentCamera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	UChildActorComponent* DeathCamera;
	
	/**
	 * \brief 1인칭 카메라의 스프링 암
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	USpringArmComponent* FirstPersonCameraSpringArm;

	/**
	 * \brief 1인칭 카메라
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	UChildActorComponent* FirstPersonCamera;

	/**
	 * \brief 1인칭 에이밍 카메라
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	UChildActorComponent* FirstPersonAimingCamera;

	/**
	 * \brief 3인칭 스텐딩 카메라의 스프링 암
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	USpringArmComponent* ThirdPersonStandCameraSpringArm;

	/**
	 * \brief 3인칭 스텐딩 카메라
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	UChildActorComponent* ThirdPersonStandCamera;

	/**
	 * \brief 3인칭 앉기 카메라의 스프링 암
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	USpringArmComponent* ThirdPersonCrouchCameraSpringArm;

	/**
	 * \brief 3인칭 앉기 카메라
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	UChildActorComponent* ThirdPersonCrouchCamera;

	/**
	 * \brief 3인칭 엎드리기 카메라의 스프링 암
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	USpringArmComponent* ThirdPersonProneCameraSpringArm;

	/**
	 * \brief 3인칭 엎드리기 카메라
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	UChildActorComponent* ThirdPersonProneCamera;
	
	// ----------------------- Camera End ----------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "PlayerState")
	bool bIsFirstPerson = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "PlayerState")
	bool bIsAiming = false;

	UPROPERTY()
	FTimerHandle HealthRegenTimerHandle;

	UPROPERTY()
	FTimerHandle HealTimerHandle;
};
