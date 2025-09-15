// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/ThrowProjectileAnimNotify.h"

#include "Actor/Projectile/BaseProjectile.h"
#include "Character/FPSUILogicCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Controller/FPSUILogicController.h"

void UThrowProjectileAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp->GetOwner() && MeshComp->GetOwner()->HasAuthority())
	{
		AFPSUILogicCharacter* CurrentCharacter = Cast<AFPSUILogicCharacter>(MeshComp->GetOwner());
		if (CurrentCharacter)
		{
			FVector ThrowLocation = MeshComp->GetSocketLocation(ThrowSocketName);;
			
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.ObjectFlags |= RF_Transient;
			
			AFPSUILogicController* CurrentController = Cast<AFPSUILogicController>(CurrentCharacter->GetController());

			TSubclassOf<ABaseProjectile> CurrentProjectileClass;

			bIsLethal ? CurrentProjectileClass = CurrentController->GetLethalClass() : CurrentProjectileClass = CurrentController->GetTacticalClass();
			
			if (!CurrentProjectileClass)
				return;

			bIsLethal ? CurrentCharacter->CharacterCarryAmmo.AddLethalProjectile(-1) : CurrentCharacter->CharacterCarryAmmo.AddTacticalProjectile(-1);
			
			ABaseProjectile* SpawnedProjectile = CurrentCharacter->GetWorld()->SpawnActor<ABaseProjectile>(CurrentProjectileClass, FTransform(FRotator(), ThrowLocation), SpawnInfo);

			
			if (SpawnedProjectile)
			{
				if (SpawnedProjectile->Collision && CurrentController)
				{
					SpawnedProjectile->Collision->AddImpulse(CurrentCharacter->CurrentCamera->GetForwardVector() * ProjectileSpeed);
					SpawnedProjectile->SetProjectileOwner(CurrentController);
				}
			}
		}
	}
}
