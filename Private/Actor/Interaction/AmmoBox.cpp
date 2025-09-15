// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Interaction/AmmoBox.h"

#include "Actor/Projectile/BaseProjectile.h"
#include "Actor/Weapon/BaseWeapon.h"
#include "Character/FPSActionLogicCharacter.h"
#include "Character/FPSUILogicCharacter.h"
#include "Controller/FPSWeaponLogicController.h"

AAmmoBox::AAmmoBox()
{
	Ammobox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Melee"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> AmmoboxMesh(TEXT("StaticMesh'/Game/Assets/AmmoBox/German_Army_MG43_Ammo_Box/0_Object_0.0_Object_0'"));
	if (AmmoboxMesh.Succeeded())
	{
		Ammobox->SetStaticMesh(AmmoboxMesh.Object);
	}
}

void AAmmoBox::Interaction_Implementation(AFPSActionLogicCharacter* Character)
{
	Super::Interaction_Implementation(Character);

	if (UseCharacterArr.Contains(Character))
		return;

	if (!Character->CurrentWeapon)
		return;
	
	Character->CharacterCarryAmmo.AddWeaponCarryAmmo(Character->CurrentWeapon->WeaponType, 99999);
	if (AFPSWeaponLogicController* CurrentController = Cast<AFPSWeaponLogicController>(Character->GetController()))
	{
		if (CurrentController->GetLethalClass())
		{
			Character->CharacterCarryAmmo.AddLethalProjectile(999);
		}
		if (CurrentController->GetLethalClass())
		{
			Character->CharacterCarryAmmo.AddTacticalProjectile(999);
		}
	}
	
	
	UseCharacterArr.Add(Character);

	FTimerHandle CoolDownTimerHandle;
	
	GetWorldTimerManager().SetTimer(
		CoolDownTimerHandle,
		this,
		&AAmmoBox::UseCoolTimerDown,
		CoolTime,
		false
	);
}

void AAmmoBox::UseCoolTimerDown()
{
	if (UseCharacterArr.IsValidIndex(0))
		UseCharacterArr.RemoveAt(0);
}
