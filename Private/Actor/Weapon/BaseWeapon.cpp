// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/BaseWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Actor/Bullet/BaseBullet.h"
#include "Character/FPSUILogicCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Controller/FPSUILogicController.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Struct/WeaponStruct.h"

DEFINE_LOG_CATEGORY(LOG_BaseWeapon);

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	
	InteractionCapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>("InteractionCapsuleCollision");
	InteractionCapsuleCollision->SetupAttachment(RootComponent);
	
	AimCameraLoc = CreateDefaultSubobject<USceneComponent>("AimCameraLoc");
	AimCameraLoc->SetupAttachment(RootComponent);

	ShotPoint = CreateDefaultSubobject<USceneComponent>("FirePoint");
	ShotPoint->SetupAttachment(RootComponent);

	
	
}

void ABaseWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ABaseWeapon, CurrentAmmo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ABaseWeapon, ShotType, COND_None, REPNOTIFY_Always);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	SetReplicateMovement(true);
	if (!WeaponDataTable)
		return;

	if (WeaponDTName.IsNone())
		return;
	
	FWeaponData* WeaponData =
		WeaponDataTable->FindRow<FWeaponData>(WeaponDTName, TEXT("General"));

	if (!WeaponData)
		return;

	BulletSpeed = WeaponData->BulletSpeed;
	HeadDamage = WeaponData->HeadDamage;
	BodyDamage = WeaponData->BodyDamage;
	ArmDamage = WeaponData->ArmDamage;
	HandDamage = WeaponData->HandDamage;
	LegDamage = WeaponData->LegDamage;
	FootDamage = WeaponData->FootDamage;
	Rpm = WeaponData->RPM;
	RecoilMultiply = WeaponData->RecoilMultiply;
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWeapon::OnRep_CurrentAmmo()
{
	AFPSUILogicCharacter* CurrentCharacter =  Cast<AFPSUILogicCharacter>(GetAttachParentActor());

	if (!CurrentCharacter)
		return;

	AFPSUILogicController* CurrentController = Cast<AFPSUILogicController>(CurrentCharacter->GetController());
	
	if (!CurrentController)
	{
		return;
	}
		

	CurrentController->ClientUpdateWeaponAmmoUI(CurrentAmmo);
}

void ABaseWeapon::FireBullet()
{
	if (!HasAuthority())
		return;

	CurrentAmmo--;

	if (bSpawnBulletBP)
	{
		SpawnBullet();
		return;
	}

	if (BulletClass)
	{
		//UKismetSystemLibrary::PrintString(GetWorld(), *ShotPoint->GetComponentLocation().ToString());
		const FTransform Transform(FRotator(0,0, 0), ShotPoint->GetComponentLocation());
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.Instigator = Cast<APawn>(Params.Owner);
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		ABaseBullet* Bullet = GetWorld()->SpawnActorDeferred<ABaseBullet>
		(
			BulletClass,
			Transform,
			Params.Owner,
			Params.Instigator,
			Params.SpawnCollisionHandlingOverride
		);

		if (Bullet)
		{
			Bullet->BulletSpeed = BulletSpeed;

			if (ACharacter* Shotter = Cast<ACharacter>(GetParentActor()))
			{
				Bullet->Shotter = Shotter;
			}
			Bullet->SetBulletDamage(HeadDamage, BodyDamage, ArmDamage, HandDamage, LegDamage, FootDamage);
			Bullet->FinishSpawning(Bullet->GetTransform());
		}
	}
}

void ABaseWeapon::MuzzleFlash()
{
	if (FireEffectMuzzle)
	{
		UE_LOG(LOG_BaseWeapon, Error, TEXT("총기 사운드가 없다니까요?"));
	}
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		FireEffectMuzzle,
		ShotPoint->GetComponentLocation()
	);
}

void ABaseWeapon::PlayFireSound()
{
	if (HasAuthority())
		return;
	
	if (!FireSound)
	{
		UE_LOG(LOG_BaseWeapon, Error, TEXT("총기 사운드가 없다니까요?"));
		return;
	}
	
	
	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		FireSound,
		ShotPoint->GetComponentLocation()
	);
	
}

int ABaseWeapon::GetCurrentAmmoCount() const
{
	return CurrentAmmo;
}

int ABaseWeapon::GetMaxAmmoCount() const
{
	return MaxAmmo;
}

FTransform ABaseWeapon::GetLeftHandIKTransform() const
{
	if (!IKSocketMesh)
	{
		UE_LOG(LOG_BaseWeapon, Error, TEXT("IKSocketMesh is not valid"));
		return FTransform();
	}

	return IKSocketMesh->GetSocketTransform(FName("LeftHandIKSocket"), RTS_World);
}

void ABaseWeapon::Reload(int NewAmmo)
{
	CurrentAmmo = NewAmmo;
}


void ABaseWeapon::ChangeShotType_Implementation()
{
	
	
	AFPSUILogicCharacter* CurrentCharacter =  Cast<AFPSUILogicCharacter>(GetAttachParentActor());

	if (!CurrentCharacter)
		return;

	AFPSUILogicController* CurrentController = Cast<AFPSUILogicController>(CurrentCharacter->GetController());
	
	if (!CurrentController)
	{
		return;
	}

	if (ShotType == ShotTypeA)
	{
		ShotType = ShotTypeB;
		CurrentController->ClientSetShotTypeB();
	}
	else
	{
		ShotType = ShotTypeA;
		CurrentController->ClientSetShotTypeA();
	}
	
	
}

UTexture2D* ABaseWeapon::GetIcon() const
{
	if (WeaponIcon)
		return WeaponIcon;

	UE_LOG(LOG_BaseWeapon, Error, TEXT("이미지를 넣어주세요"));
	return nullptr;
}

FTransform ABaseWeapon::GetRightHandTransform() const
{
	return RightHandTransform;
}

