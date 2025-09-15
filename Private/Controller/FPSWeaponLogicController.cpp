// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/FPSWeaponLogicController.h"

#include "Actor/Projectile/BaseProjectile.h"
#include "Actor/Weapon/BaseWeapon.h"
#include "Character/FPSUILogicCharacter.h"
#include "Character/FPSWeaponLogicCharacter.h"
#include "Net/UnrealNetwork.h"

void AFPSWeaponLogicController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Attack", IE_Pressed ,this, &AFPSWeaponLogicController::AttackPressed);
	InputComponent->BindAction("Attack", IE_Released ,this, &AFPSWeaponLogicController::AttackReleased);

	InputComponent->BindAction("Aiming", IE_Pressed ,this, &AFPSWeaponLogicController::AimingPressed);
	InputComponent->BindAction("Aiming", IE_Released ,this, &AFPSWeaponLogicController::AimingReleased);

	InputComponent->BindAction("Reload", IE_Pressed ,this, &AFPSWeaponLogicController::Reload);
	
	InputComponent->BindAction("ChangeShotType", IE_Pressed ,this, &AFPSWeaponLogicController::ChangeShotType);
	
	InputComponent->BindAction("EquipMainWeapon", IE_Pressed ,this, &AFPSWeaponLogicController::ChangeWeaponToMainWeapon);
	
	InputComponent->BindAction("EquipSubWeapon", IE_Pressed ,this, &AFPSWeaponLogicController::ChangeWeaponToSubWeapon);
}

void AFPSWeaponLogicController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSWeaponLogicController, MainWeaponClass, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSWeaponLogicController, SubWeaponClass, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSWeaponLogicController, LethalClass, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSWeaponLogicController, TacticalClass, COND_None, REPNOTIFY_Always);
}

AFPSWeaponLogicCharacter* AFPSWeaponLogicController::GetWeaponLogicCharacter() const
{
	return Cast<AFPSWeaponLogicCharacter>(GetPawn());
}

void AFPSWeaponLogicController::AttackPressed()
{
	if (!bIsCanWork || !bIsPlayerAlive)
		return;

	if (GetWeaponLogicCharacter())
	{
		GetWeaponLogicCharacter()->ServerAttack();
	}
}

void AFPSWeaponLogicController::AttackReleased()
{
	if (!bIsCanWork || !bIsPlayerAlive)
		return;

	if (GetWeaponLogicCharacter())
	{
		GetWeaponLogicCharacter()->ServerStopRecoil();
	}
}

void AFPSWeaponLogicController::AimingPressed()
{
	if (!bIsPlayerAlive)
		return;

	GetWeaponLogicCharacter()->Aiming();
}

void AFPSWeaponLogicController::AimingReleased()
{
	if (!bIsPlayerAlive)
		return;

	GetWeaponLogicCharacter()->NonAiming();
}

void AFPSWeaponLogicController::Reload()
{
	if (!bIsPlayerAlive)
		return;

	GetWeaponLogicCharacter()->ServerTryReload();
}

void AFPSWeaponLogicController::ChangeWeaponToMainWeapon()
{
	if (!bIsPlayerAlive && !GetWeaponLogicCharacter()->MainWeapon)
		return;

	GetWeaponLogicCharacter()->ServerChangeWeaponToMainWeapon();
}

void AFPSWeaponLogicController::ChangeWeaponToSubWeapon()
{
	if (!bIsPlayerAlive && !GetWeaponLogicCharacter()->SubWeapon)
		return;

	GetWeaponLogicCharacter()->ServerChangeWeaponToSubWeapon();
}

void AFPSWeaponLogicController::ChangeShotType()
{
	if (!bIsPlayerAlive)
		return;

	GetWeaponLogicCharacter()->ServerChangeShotType();
}

TSubclassOf<ABaseWeapon> AFPSWeaponLogicController::GetMainWeaponClass() const
{
	if (MainWeaponClass)
	{
		return MainWeaponClass;
	}

	return nullptr;
	
}

TSubclassOf<ABaseWeapon> AFPSWeaponLogicController::GetSubWeaponClass() const
{
	if (SubWeaponClass)
	{
		return SubWeaponClass;
	}

	return nullptr;
}

TSubclassOf<ABaseProjectile> AFPSWeaponLogicController::GetLethalClass() const
{
	if (LethalClass)
	{
		return LethalClass;
	}

	return nullptr;
}

TSubclassOf<ABaseProjectile> AFPSWeaponLogicController::GetTacticalClass() const
{
	if (TacticalClass)
	{
		return TacticalClass;
	}

	return nullptr;
}

void AFPSWeaponLogicController::SpawnWeaponAndEquipToMain_Implementation(TSubclassOf<ABaseWeapon> TargetWeaponClass)
{

	if (!GetPawn())
		return;
	
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;
	ABaseWeapon* Weapon = GetWorld()->SpawnActor<ABaseWeapon>(TargetWeaponClass, GetPawn()->GetActorTransform(), SpawnInfo);

	if (!Weapon)
		return;

	AFPSUILogicCharacter* CurrentPawn = Cast<AFPSUILogicCharacter>( GetPawn());

	if (!CurrentPawn)
		return;

	if (CurrentPawn->MainWeapon)
	{
		CurrentPawn->MainWeapon->Destroy();
		CurrentPawn->MainWeapon = nullptr;
	}

	CurrentPawn->MainWeapon = Weapon;

	CurrentPawn->ChangeWeaponToMainWeapon();
	
}

void AFPSWeaponLogicController::SpawnWeaponAndEquipToSub_Implementation(TSubclassOf<ABaseWeapon> TargetWeaponClass)
{
	if (!GetPawn())
		return;
	
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;
	ABaseWeapon* Weapon = GetWorld()->SpawnActor<ABaseWeapon>(TargetWeaponClass, GetPawn()->GetActorTransform(), SpawnInfo);

	if (!Weapon)
		return;

	AFPSUILogicCharacter* CurrentPawn = Cast<AFPSUILogicCharacter>( GetPawn());

	if (!CurrentPawn)
		return;

	if (CurrentPawn->SubWeapon)
	{
		CurrentPawn->SubWeapon->Destroy();
		CurrentPawn->SubWeapon = nullptr;
	}

	CurrentPawn->SubWeapon = Weapon;

	CurrentPawn->ChangeWeaponToSubWeapon();
}

void AFPSWeaponLogicController::SetMainWeaponClass_Implementation(TSubclassOf<ABaseWeapon> NewMainWeaponClass)
{
	MainWeaponClass = NewMainWeaponClass;
}

void AFPSWeaponLogicController::SetSubWeaponClass_Implementation(TSubclassOf<ABaseWeapon> NewSubWeaponClass)
{
	SubWeaponClass = NewSubWeaponClass;
}

void AFPSWeaponLogicController::SetLethalClass_Implementation(TSubclassOf<ABaseProjectile> NewLethalClass)
{
	LethalClass = NewLethalClass;
}

void AFPSWeaponLogicController::SetTacticalClass_Implementation(TSubclassOf<ABaseProjectile> NewTacticalClass)
{
	TacticalClass = NewTacticalClass;
}
