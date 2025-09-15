// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FPSWeaponLogicCharacter.h"

#include "Actor/Weapon/BaseWeapon.h"
#include "AnimInstance/FPSBaseAnimInstance.h"
#include "Controller/FPSUILogicController.h"
#include "Controller/FPSWeaponLogicController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LOG_FPSWeaponLogicCharacter);

void AFPSWeaponLogicCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(AFPSWeaponLogicCharacter, PlayerEquipWeaponType, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSWeaponLogicCharacter, bIsNotFireDelay, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSWeaponLogicCharacter, bCanAttack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSWeaponLogicCharacter, RandomSeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSWeaponLogicCharacter, CurrentWeapon, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSWeaponLogicCharacter, MainWeapon, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSWeaponLogicCharacter, SubWeapon, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSWeaponLogicCharacter, bIsWeaponEquip, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSWeaponLogicCharacter, CharacterCarryAmmo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSWeaponLogicCharacter, bIsAttacking, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSWeaponLogicCharacter, bUseLeftHandIK, COND_None, REPNOTIFY_Always);
}

void AFPSWeaponLogicCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		RandomSeed = FMath::Rand(); // 랜덤 시드 생성
	}
}

void AFPSWeaponLogicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetAimCameraToWeaponCamera();
}

void AFPSWeaponLogicCharacter::CanFire()
{
	bIsNotFireDelay = true;
}



void AFPSWeaponLogicCharacter::ServerAttack_Implementation()
{
	if (!bIsNotFireDelay)
		return;
	
	switch (PlayerEquipWeaponType) {
	case EEquipWeaponType::None:
		// 플레이가 들고 있는 무기가 없다면 아무것도 안함
		break;
	case EEquipWeaponType::Melee:
		// 플레이어가 근접무기를 들고 있는 경우에는 근접 공격을 함
		MultiMontagePlayWithSession(UpperBodyMontage, MeleeAttackSectionName, MeleeAttackMontagePlayRate);
		break;
	case EEquipWeaponType::AR:
	case EEquipWeaponType::Pistol:
		{
			// 총을 들고 있는 경우
			if (!CurrentWeapon)
			{
				UE_LOG(LOG_FPSWeaponLogicCharacter, Error, TEXT("무기가 없는데 EquipType가 AR또는 Pistol일 수 있습니까?"));
				break;
			}
		
			ServerSpeedChange();

			ServerFire();	// 일단 총 쏘기

			FTimerHandle* CurrentFireTimerHandle = nullptr;
			
			switch (CurrentWeapon->ShotType)
			{
			case EShotType::SemiAuto:
				break;
			case EShotType::Auto:
				CurrentFireTimerHandle = &AutoFireTimerHandle;
				break;
			case EShotType::ThreeTabBurst:
				CurrentFireTimerHandle = &ThreeTabFireTimerHandle;
				break;
			case EShotType::TwoTabBurst:
				CurrentFireTimerHandle = &TwoTabFireHandle;
				break;
			}

			// 타이머 핸들이 Nullptr이 아니라면 연사(또는 점사)이므로 사격 타이머 돌림
			if (CurrentFireTimerHandle)
			{
				GetWorld()->GetTimerManager().SetTimer(
					*CurrentFireTimerHandle,
					this,
					&AFPSWeaponLogicCharacter::ServerFire,
					CurrentWeapon->Rpm,
					true
				);
			}
			
			break;
		}
	}
}

void AFPSWeaponLogicCharacter::ServerFire_Implementation()
{
	if (!bCanAttack)
		return;
	
	if (!CurrentWeapon)
	{
		ServerStopAttack();
		return;
	}

	if (CurrentWeapon->GetCurrentAmmoCount() < 1)
	{
		ServerStopAttack();
		return;
	}

	if (RecoilTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(RecoilTimer);
	}
	
	CurrentWeapon->FireBullet();

	bIsNotFireDelay = false;

	// 단발 광클 방지
	GetWorld()->GetTimerManager().SetTimer(
		RecoilTimer,
		this,
		&AFPSWeaponLogicCharacter::CanFire,
		CurrentWeapon->Rpm,
		true
		);

	switch (CurrentWeapon->ShotType) {
	case EShotType::ThreeTabBurst:
	case EShotType::TwoTabBurst:
		if (ShotCount++ >= (CurrentWeapon->ShotType == EShotType::ThreeTabBurst ? 2 : 1))
		{
			ServerStopAttack();
			ShotCount = 0;
		}
		break;
		
	default:
		break;
	}

	MultiFire(
		FMath::FRandRange(RandomRecoilRotateRollMin, RandomRecoilRotateRollMax),
		FMath::FRandRange(RandomRecoilRotateYawMin, RandomRecoilRotateYawMax),
		FMath::FRandRange(RandomRecoilRotatePitchMin, RandomRecoilRotatePitchMax),
		FMath::FRandRange(RandomRecoilLocationXMin, RandomRecoilLocationXMax),
		FMath::FRandRange(RandomRecoilLocationYMin, RandomRecoilLocationYMax),
		FMath::FRandRange(RandomRecoilLocationZMin, RandomRecoilLocationZMax)
	);
}

void AFPSWeaponLogicCharacter::MultiFire_Implementation(float RandomRecoilRotateRoll, float RandomRecoilRotatePitch, float RandomRecoilRotateYaw, float RandomRecoilVectorX, float RandomRecoilVectorY, float RandomRecoilVectorZ)
{
	if (!CurrentWeapon)
		return;

	//bIsAttacking = true;
	
	if (UFPSBaseAnimInstance* CurrentAnimInstance
		= Cast<UFPSBaseAnimInstance>(GetMesh()->GetAnimInstance())
	)
	{
		CurrentAnimInstance->ProceduralRecoil(
			CurrentWeapon->RecoilMultiply
				* FRotator(RandomRecoilRotatePitch, RandomRecoilRotateYaw, RandomRecoilRotateRoll),
			CurrentWeapon->RecoilMultiply
				* FVector(RandomRecoilVectorX, RandomRecoilVectorY, RandomRecoilVectorZ)
		);
	}
	
	CurrentWeapon->MuzzleFlash();
	CurrentWeapon->PlayFireSound();
	LookUp(-0.4);
}

void AFPSWeaponLogicCharacter::ServerStopAttack_Implementation()
{
	MultiStopAttack();
}

void AFPSWeaponLogicCharacter::MultiStopAttack_Implementation()
{
	if (AutoFireTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(AutoFireTimerHandle);
	}

	if (ThreeTabFireTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(ThreeTabFireTimerHandle);
	}

	if (TwoTabFireHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(TwoTabFireHandle);
	}

	//bIsAttacking = false;
}

void AFPSWeaponLogicCharacter::ServerStopRecoil_Implementation()
{
	if (!CurrentWeapon)
		return;

	FTimerHandle CanRecoilTimerHandle;
	GetWorldTimerManager().SetTimer(
		CanRecoilTimerHandle,
		this,
		&AFPSWeaponLogicCharacter::CanFire,
		CurrentWeapon->Rpm,
		false
		);

	MultiStopRecoil();
}

void AFPSWeaponLogicCharacter::MultiStopRecoil_Implementation()
{
	if (AutoFireTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(AutoFireTimerHandle);
	}

	if (RecoilTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(RecoilTimer);
	}

	bIsAttacking = false;
}


void AFPSWeaponLogicCharacter::Aiming()
{
	switch (PlayerEquipWeaponType) {
	case EEquipWeaponType::AR:
	case EEquipWeaponType::Pistol:
		{
			AFPSWeaponLogicController* CurrentController = Cast<AFPSWeaponLogicController>(GetController());
			if (CurrentController && FirstPersonAimingCamera)
			{
				CurrentController->SetViewTargetWithBlend(FirstPersonAimingCamera->GetChildActor(), 0.4f);
				ServerSetbIsAiming(true);
				ServerSpeedChange();
				CurrentCamera = FirstPersonAimingCamera;
			}
			break;
		}
	}
}

void AFPSWeaponLogicCharacter::NonAiming()
{
	AFPSWeaponLogicController* CurrentController = Cast<AFPSWeaponLogicController>(GetController());
	if (CurrentController && FirstPersonCamera)
	{
		CurrentController->SetViewTargetWithBlend(FirstPersonCamera->GetChildActor(), 0.f);
		ServerSetbIsAiming(false);
		ServerSpeedChange();
		CurrentCamera = FirstPersonCamera;
	}
}



void AFPSWeaponLogicCharacter::ServerTryReload_Implementation()
{
	MultiTryReload();
}

void AFPSWeaponLogicCharacter::MultiTryReload_Implementation()
{
	TryReload();
}

void AFPSWeaponLogicCharacter::TryReload()
{

	if (!CurrentWeapon)
	{
		UE_LOG(LOG_FPSWeaponLogicCharacter, Warning, TEXT("무기가 없으므로 인해 재장전 실패"));
		return;
	}
	if ((CurrentWeapon->GetMaxAmmoCount() == CurrentWeapon->GetCurrentAmmoCount()) || CharacterCarryAmmo.GetWeaponCarryAmmo(CurrentWeapon->WeaponType) <= 0)
	{
		return;
	}

	PlayMontageWithSession(UpperBodyMontage, FName(TEXT("ReloadRifle")));
	SetUseLeftHandIK(false);
	SetCanAttack(false);
}

void AFPSWeaponLogicCharacter::ReloadAmmo()
{
	if (!CurrentWeapon)
		return;

	if (CurrentWeapon->GetMaxAmmoCount() != CurrentWeapon->GetCurrentAmmoCount()
		&& CharacterCarryAmmo.GetWeaponCarryAmmo(CurrentWeapon->WeaponType) > 0 && HasAuthority())
	{
		int NeedAmmo = CurrentWeapon->GetMaxAmmoCount()- CurrentWeapon->GetCurrentAmmoCount();
		
		if (CharacterCarryAmmo.GetWeaponCarryAmmo(CurrentWeapon->WeaponType) >= NeedAmmo)
		{
			//무기 재장전
			CurrentWeapon->Reload(CurrentWeapon->GetMaxAmmoCount());
			CharacterCarryAmmo.SetWeaponCarryAmmo(CurrentWeapon->WeaponType, CharacterCarryAmmo.GetWeaponCarryAmmo(CurrentWeapon->WeaponType) - NeedAmmo);
		}
		else
		{
			CurrentWeapon->Reload(CurrentWeapon->GetCurrentAmmoCount() + CharacterCarryAmmo.GetWeaponCarryAmmo(CurrentWeapon->WeaponType));
			CharacterCarryAmmo.SetWeaponCarryAmmo(CurrentWeapon->WeaponType, 0);
		}
	}
}

FTransform AFPSWeaponLogicCharacter::GetLeftHandIKTransform()
{
	if(!CurrentWeapon || !bIsWeaponEquip)
	{
		//UE_LOG(LOG_FPSWeaponLogicCharacter, Warning, TEXT("무기 없음"));
		return FTransform();
	}
	
	FVector NewLocation;
	FRotator NewRotation;
	
	GetMesh()->TransformToBoneSpace(FName(TEXT("hand_r")), CurrentWeapon->GetLeftHandIKTransform().GetLocation(), CurrentWeapon->GetLeftHandIKTransform().Rotator(), NewLocation, NewRotation);
	FTransform ReturnTransform =  FTransform(NewRotation,NewLocation);
	return ReturnTransform;
}

bool AFPSWeaponLogicCharacter::GetUseLeftHandIK()
{
	switch (PlayerEquipWeaponType) {
	case EEquipWeaponType::None:
	case EEquipWeaponType::Melee:
		return false;
	case EEquipWeaponType::AR:
	case EEquipWeaponType::Pistol:
		return bUseLeftHandIK;
	}
	
	return false;
}

void AFPSWeaponLogicCharacter::SetUseLeftHandIK(bool NewbUseLeftHandIK)
{
	bUseLeftHandIK = NewbUseLeftHandIK;
}

bool AFPSWeaponLogicCharacter::GetCanAttack()
{
	return bCanAttack;
}

void AFPSWeaponLogicCharacter::SetCanAttack(bool NewbCanAttack)
{
	bCanAttack = NewbCanAttack;
}

void AFPSWeaponLogicCharacter::ClientHitDamage_Implementation(AFPSBaseCharacter* Attacker)
{
	
}


FRotator AFPSWeaponLogicCharacter::GetAimRotator()
{
	return FRotator(
		0,
		0,
		UKismetMathLibrary::SelectFloat(
			GetControlRotation().Pitch - 360,
			GetControlRotation().Pitch * -1,
			GetControlRotation().Pitch > 180
			) / 3
		);
}

void AFPSWeaponLogicCharacter::ServerSetbIsAiming_Implementation(bool NewbIsAiming)
{
	bIsAiming = NewbIsAiming;
	MultiSetbIsAiming(NewbIsAiming);
}

void AFPSWeaponLogicCharacter::MultiSetbIsAiming_Implementation(bool NewbIsAiming)
{
	bIsAiming = NewbIsAiming;
}

void AFPSWeaponLogicCharacter::ServerChangeWeaponToMainWeapon_Implementation()
{
	MultiChangeWeaponToMainWeapon();
}

void AFPSWeaponLogicCharacter::MultiChangeWeaponToMainWeapon_Implementation()
{
	ChangeWeaponToMainWeapon();
}

void AFPSWeaponLogicCharacter::ChangeWeaponToMainWeapon()
{

	if (!MainWeapon || CurrentWeapon == MainWeapon)
		return;

	if (SubWeapon)
	{
		SubWeapon->SetActorHiddenInGame(true);
	}

	MainWeapon->SetActorHiddenInGame(false);

	CurrentWeapon = MainWeapon;

	CurrentWeapon->AttachToComponent(
		GetMesh(),
		FAttachmentTransformRules(
			EAttachmentRule::KeepRelative, true),
			FName(TEXT("RightWeaponSocket")
			)
		);

	CurrentWeapon->SetActorRelativeTransform(CurrentWeapon->GetRightHandTransform());

	PlayerEquipWeaponType = CurrentWeapon->WeaponEquipType;

	bIsWeaponEquip = true;

	if (AFPSUILogicController* CurrentController =  Cast<AFPSUILogicController>(GetController()))
	{
		CurrentController->ClientUpdateWeaponIconUI(CurrentWeapon->GetIcon());
		CurrentController->ClientUpdateWeaponAmmoUI(CurrentWeapon->GetCurrentAmmoCount());
		CurrentController->ClientUpdateCharacterCarryAmmo(CharacterCarryAmmo.GetWeaponCarryAmmo(CurrentWeapon->WeaponType));
		CurrentController->ClientSetShotTypeIcon(CurrentWeapon->ShotTypeA, CurrentWeapon->ShotTypeB);
		CurrentWeapon->ShotType == CurrentWeapon->ShotTypeA ? CurrentController->ClientSetShotTypeA() : CurrentController->ClientSetShotTypeB();
	}
}

void AFPSWeaponLogicCharacter::ServerChangeWeaponToSubWeapon_Implementation()
{
	MultiChangeWeaponToSubWeapon();
}

void AFPSWeaponLogicCharacter::MultiChangeWeaponToSubWeapon_Implementation()
{
	ChangeWeaponToSubWeapon();
}

void AFPSWeaponLogicCharacter::ChangeWeaponToSubWeapon()
{
	if (!SubWeapon || CurrentWeapon == SubWeapon)
		return;

	if (MainWeapon)
	{
		MainWeapon->SetActorHiddenInGame(true);
	}

	SubWeapon->SetActorHiddenInGame(false);

	CurrentWeapon = SubWeapon;

	CurrentWeapon->AttachToComponent(
		GetMesh(),
		FAttachmentTransformRules(
			EAttachmentRule::KeepRelative, true),
			FName(TEXT("RightWeaponSocket")
			)
		);

	CurrentWeapon->SetActorRelativeTransform(CurrentWeapon->GetRightHandTransform());

	PlayerEquipWeaponType = CurrentWeapon->WeaponEquipType;

	bIsWeaponEquip = true;

	if (AFPSUILogicController* CurrentController =  Cast<AFPSUILogicController>(GetController()))
	{
		CurrentController->ClientUpdateWeaponIconUI(CurrentWeapon->GetIcon());
		CurrentController->ClientUpdateWeaponAmmoUI(CurrentWeapon->GetCurrentAmmoCount());
		CurrentController->ClientUpdateCharacterCarryAmmo(CharacterCarryAmmo.GetWeaponCarryAmmo(CurrentWeapon->WeaponType));
		CurrentController->ClientSetShotTypeIcon(CurrentWeapon->ShotTypeA, CurrentWeapon->ShotTypeB);
		CurrentWeapon->ShotType == CurrentWeapon->ShotTypeA ? CurrentController->ClientSetShotTypeA() : CurrentController->ClientSetShotTypeB();
	}
}

void AFPSWeaponLogicCharacter::SetAimCameraToWeaponCamera()
{
	if (!CurrentWeapon || !FirstPersonAimingCamera)
		return;

	FirstPersonAimingCamera->GetChildActor()->SetActorLocation(CurrentWeapon->AimCameraLoc->GetComponentLocation());
}

void AFPSWeaponLogicCharacter::CurrentWeaponHidden(bool NewHidden)
{
	if (CurrentWeapon)
		CurrentWeapon->SetActorHiddenInGame(NewHidden);
}

void AFPSWeaponLogicCharacter::ServerChangeShotType_Implementation()
{
	if (!bIsNotFireDelay || !CurrentWeapon)
		return;
	
	bIsNotFireDelay = false;

	CurrentWeapon->ChangeShotType();

	FTimerHandle ChangeShotTypeTimerHandle;
	
	GetWorldTimerManager().SetTimer(
		ChangeShotTypeTimerHandle,
		this,
		&AFPSWeaponLogicCharacter::CanFire,
		0.1f,
		false
	);

}

