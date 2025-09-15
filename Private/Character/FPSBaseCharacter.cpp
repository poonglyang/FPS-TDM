// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FPSBaseCharacter.h"

#include "Camera/CameraActor.h"
#include "Controller/FPSBaseController.h"
#include "EngineOverride/SkeletalMesh/FuckTestSkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LOG_FPSBaseCharacter);

// Sets default values
AFPSBaseCharacter::AFPSBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("SkeletalMesh'/Game/Assets/IdaFaber/Meshes/Girl/SK_MMO_CHAMPION_F_lingerie.SK_MMO_CHAMPION_F_lingerie'"));
	
	if (CharacterMeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
		UE_LOG(LOG_FPSBaseCharacter, Log, TEXT("MeshCallSuccess"));
	}
	else {
		UE_LOG(LOG_FPSBaseCharacter, Error, TEXT("MeshCallFail"));
	}

	CharacterState = FCharacterState();
	
	// ------------------------- Mesh Setting -----------------------------------
	Head = CreateDefaultSubobject<USkeletalMeshComponent>("Head");
	Head->SetupAttachment(GetMesh());

	UpperBody = CreateDefaultSubobject<USkeletalMeshComponent>("UpperBody");
	UpperBody->SetupAttachment(GetMesh());
	UpperBody->bAlwaysCreatePhysicsState = true;
	UpperBody -> bEnablePerPolyCollision = true;
	
	Armor = CreateDefaultSubobject<USkeletalMeshComponent>("Armor");
	Armor->SetupAttachment(UpperBody);

	Clavicle = CreateDefaultSubobject<USkeletalMeshComponent>("Clavicle");
	Clavicle->SetupAttachment(UpperBody);

	UpperArm = CreateDefaultSubobject<USkeletalMeshComponent>("UpperArm");
	UpperArm->SetupAttachment(Clavicle);

	LowerArm = CreateDefaultSubobject<USkeletalMeshComponent>("LowerArm");
	LowerArm->SetupAttachment(UpperArm);

	Hand = CreateDefaultSubobject<USkeletalMeshComponent>("Hand");
	Hand->SetupAttachment(LowerArm);

	LowerBody = CreateDefaultSubobject<USkeletalMeshComponent>("LowerBody");
	LowerBody->SetupAttachment(GetMesh());

	Foot = CreateDefaultSubobject<USkeletalMeshComponent>("Foot");
	Foot->SetupAttachment(LowerBody);
	// ------------------------- Mesh Setting End -------------------------------
	
	// ------------------------- Camera Setting ---------------------------------
	// FirstPerson Camera Spring Arm Setting
	FirstPersonCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("FirstPersonCameraSpringArm"));

	if (GetMesh()->GetBoneIndex(FName(TEXT("head"))) != INDEX_NONE)
	{
		UE_LOG(LOG_FPSBaseCharacter, Log, TEXT("head bone is valid"));
	}
	else
	{
		UE_LOG(LOG_FPSBaseCharacter, Error, TEXT("head bone not valid"));
	}
	FirstPersonCameraSpringArm->SetupAttachment(GetMesh(), FName(TEXT("head")));
	FirstPersonCameraSpringArm->TargetArmLength = 0.f;
	FirstPersonCameraSpringArm->SetRelativeLocation(FVector(2.705270, -0.777386, -7.993353));
	FirstPersonCameraSpringArm->bUsePawnControlRotation = true;

	// FirstPerson Camera Setting
	FirstPersonCamera = CreateDefaultSubobject<UChildActorComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(FirstPersonCameraSpringArm);
	

	// FirstPersonAiming Camera Setting
	FirstPersonAimingCamera = CreateDefaultSubobject<UChildActorComponent>(TEXT("FirstPersonAimingCamera"));
	FirstPersonAimingCamera->SetupAttachment(FirstPersonCameraSpringArm);
	
	
	// ThirdPerson Stand Camera Spring Arm Setting
	ThirdPersonStandCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonStandCameraSpringArm"));
	ThirdPersonStandCameraSpringArm->SetupAttachment(RootComponent);
	ThirdPersonStandCameraSpringArm->TargetArmLength = 200.f;
	ThirdPersonStandCameraSpringArm->SetRelativeLocation(FVector(0, 0, 80));
	ThirdPersonStandCameraSpringArm->bUsePawnControlRotation = true;

	// ThirdPerson Stand Camera Setting
	ThirdPersonStandCamera = CreateDefaultSubobject<UChildActorComponent>(TEXT("ThirdPersonStandCamera"));
	ThirdPersonStandCamera->SetupAttachment(ThirdPersonStandCameraSpringArm);
	ThirdPersonStandCamera->SetRelativeLocation(FVector(0, -40, 0));
	ThirdPersonStandCamera->SetRelativeRotation(FRotator(0, 0, 5.4));
	
	
	// ThirdPerson Crouch Camera Spring Arm Setting
	ThirdPersonCrouchCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonCrouchCameraSpringArm"));
	ThirdPersonCrouchCameraSpringArm->SetupAttachment(RootComponent);
	ThirdPersonCrouchCameraSpringArm->TargetArmLength = 200.f;
	ThirdPersonCrouchCameraSpringArm->SetRelativeLocation(FVector(0, 0, 44));
	ThirdPersonCrouchCameraSpringArm->bUsePawnControlRotation = true;

	// ThirdPerson Crouch Camera Setting
	ThirdPersonCrouchCamera = CreateDefaultSubobject<UChildActorComponent>(TEXT("ThirdPersonCrouchCamera"));
	ThirdPersonCrouchCamera->SetupAttachment(ThirdPersonCrouchCameraSpringArm);
	ThirdPersonCrouchCamera->SetRelativeLocation(FVector(0, -40, 0));
	ThirdPersonCrouchCamera->SetRelativeRotation(FRotator(0, 0, 5.4));
	
	
	// ThirdPerson Prone Camera Spring Arm Setting
	ThirdPersonProneCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonProneCameraSpringArm"));
	ThirdPersonProneCameraSpringArm->SetupAttachment(RootComponent);
	ThirdPersonProneCameraSpringArm->TargetArmLength = 200.f;
	ThirdPersonProneCameraSpringArm->SetRelativeLocation(FVector(0, 0, 18));
	ThirdPersonProneCameraSpringArm->bUsePawnControlRotation = true;

	// ThirdPerson Prone Camera Setting
	ThirdPersonProneCamera = CreateDefaultSubobject<UChildActorComponent>(TEXT("ThirdPersonProneCamera"));
	ThirdPersonProneCamera->SetupAttachment(ThirdPersonProneCameraSpringArm);
	ThirdPersonProneCamera->SetRelativeLocation(FVector(0, -40, 0));
	ThirdPersonProneCamera->SetRelativeRotation(FRotator(0, 0, 5.4));
	

	// Death Camera Setting
	DeathCamera = CreateDefaultSubobject<UChildActorComponent>(TEXT("DeathCamera"));
	DeathCamera->SetupAttachment(RootComponent);
	
	// ------------------------- Camera Setting End -----------------------------
}

void AFPSBaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(AFPSBaseCharacter, PlayerStance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSBaseCharacter, bIsAiming, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSBaseCharacter, CharacterState, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSBaseCharacter, bIsFirstPerson, COND_None, REPNOTIFY_Always);
}

void AFPSBaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// FirstPersonCamera->SetChildActorClass(ACameraActor::StaticClass());
	// ThirdPersonProneCamera->SetChildActorClass(ACameraActor::StaticClass());
	// ThirdPersonCrouchCamera->SetChildActorClass(ACameraActor::StaticClass());
	// DeathCamera->SetChildActorClass(ACameraActor::StaticClass());
	// ThirdPersonStandCamera->SetChildActorClass(ACameraActor::StaticClass());
	// FirstPersonAimingCamera->SetChildActorClass(ACameraActor::StaticClass());
}

// Called when the game starts or when spawned
void AFPSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterState.SetIsGameplay(bIsGamePlay);
}

// Called every frame
void AFPSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFPSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AFPSBaseCharacter::MasterPoseToChildrenMesh()
{
	TArray<USceneComponent*> ChildrenMeshArr;
	GetMesh()->GetChildrenComponents(true, ChildrenMeshArr);
	for (USceneComponent* Child : ChildrenMeshArr)
	{
		if (USkeletalMeshComponent* MeshChild = Cast<USkeletalMeshComponent>(Child))
		{
			MeshChild->SetMasterPoseComponent(GetMesh(), true);
		}
	}
}

void AFPSBaseCharacter::ServerSetPlayerStance_Implementation(EPlayerStanceMode NewStance)
{
	PlayerStance = NewStance;
}

void AFPSBaseCharacter::ServerChangeCamera_Implementation()
{
	MultiChangeCamera();
}

void AFPSBaseCharacter::MultiChangeCamera_Implementation()
{
	ChangeCamera();
}

void AFPSBaseCharacter::ChangeCamera()
{
	AFPSBaseController* CurrentController = Cast<AFPSBaseController>(GetController());

	if (!CurrentController)
		return;
	
	if (bIsAiming)
	{
		CurrentController->SetViewTargetWithBlend(FirstPersonAimingCamera->GetChildActor(), 0);
		CurrentCamera = FirstPersonAimingCamera;
		return;
	}

	if (bIsFirstPerson)
	{
		CurrentController->SetViewTargetWithBlend(FirstPersonCamera->GetChildActor(), 0);
		CurrentCamera = FirstPersonCamera;
	}
	else
	{
		switch (PlayerStance)
		{
		case EPlayerStanceMode::Stand:
			CurrentController->SetViewTargetWithBlend(ThirdPersonStandCamera->GetChildActor(), 0);
			CurrentCamera = ThirdPersonStandCamera;
			break;

		case EPlayerStanceMode::Crouch:
			CurrentController->SetViewTargetWithBlend(ThirdPersonCrouchCamera->GetChildActor(), 0.4);
			CurrentCamera = ThirdPersonCrouchCamera;
			break;

		case EPlayerStanceMode::Prone:
			CurrentController->SetViewTargetWithBlend(ThirdPersonProneCamera->GetChildActor(), 1);
			CurrentCamera = ThirdPersonProneCamera;
			break;
		}
	}
}

void AFPSBaseCharacter::ServerMontagePlayWithSession_Implementation(UAnimMontage* Montage, FName SectionName,
                                                                    float PlayRate)
{
	MultiMontagePlayWithSession(Montage, SectionName, PlayRate);
}

void AFPSBaseCharacter::MultiMontagePlayWithSession_Implementation(UAnimMontage* Montage, FName SectionName,
                                                                   float PlayRate)
{
	PlayMontageWithSession(Montage, SectionName, PlayRate);
}

void AFPSBaseCharacter::PlayMontageWithSession(UAnimMontage* Montage, FName SectionName, float PlayRate)
{
	FString Message;
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		if (Montage && Montage->IsValidSectionName(SectionName)) // AttackMontage는 UAnimMontage* 변수
		{
			AnimInstance->Montage_Play(Montage, PlayRate);
			AnimInstance->Montage_JumpToSection(SectionName, Montage);
		}
		else
		{
			Message = FString::Printf(TEXT("받아온 몽타주 없음"));
			UE_LOG(LOG_FPSBaseCharacter, Error, TEXT("%s"), *Message);
		}
	}
	else
	{
		Message = FString::Printf(TEXT("AnimInstance 가져오기 실패"));
		UE_LOG(LOG_FPSBaseCharacter, Error, TEXT("%s"), *Message);
	}
}

void AFPSBaseCharacter::ServerStartHealthRegen_Implementation(float HealDelay, float HealAmount)
{
	if (HealthRegenTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(HealthRegenTimerHandle); 
	}
	if (HealTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(HealTimerHandle); 
	}

	GetWorldTimerManager().SetTimer(
		HealthRegenTimerHandle,
		[HealAmount, this]()  // 캡처 리스트: MyValue를 복사 캡처
		{
			this->HealthRegenStart(HealAmount);
		},
		HealDelay,
		true
	);
}

void AFPSBaseCharacter::HealthRegenStart(float HealAmount)
{
	if (HealTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(HealTimerHandle); 
	}
	
	GetWorldTimerManager().SetTimer(
		HealTimerHandle,
		[HealAmount, this]()
		{
			this->HealthRegen(HealAmount);
		},
		0.01f,
		true
	);
}

void AFPSBaseCharacter::HealthRegen(float HealAmount)
{
	if (!this)
		return;
	
	CharacterState.SetHp(CharacterState.GetHp() + HealAmount);

	if (CharacterState.GetHp() == CharacterState.GetMaxHp() && HealthRegenTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(HealthRegenTimerHandle);
	}
	
}


