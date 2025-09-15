// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Projectile/Grenade.h"

#include "NiagaraComponent.h"
#include "Character/FPSUILogicCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Controller/FPSUILogicController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AGrenade::AGrenade()
{
	ExplosionEffect = CreateDefaultSubobject<UNiagaraComponent>("ExplosionEffect");
	if (ExplosionEffect)
	{
		ExplosionEffect->bAutoActivate = false;
		ExplosionEffect->SetupAttachment(Collision);
	}
}

void AGrenade::SetProjectileOwner(AFPSUILogicController* NewOwnerController)
{
	Super::SetProjectileOwner(NewOwnerController);

	if (OwnerPlayer->GetPawn())
	{
		ExplosionRotation = FRotationMatrix::MakeFromX(OwnerPlayer->GetPawn()->GetActorForwardVector()).Rotator();
	}
}


void AGrenade::ProjectileAction()
{
	Super::ProjectileAction();
	
	TArray<FHitResult> HitResults;

	if (HasAuthority())
	{
		DetectedPlayer(HitResults,GetActorLocation() ,GetActorLocation(), GrenadeArea);
	
		for (FHitResult HitResult : HitResults)
		{
			if (AFPSUILogicCharacter* HitPlayer = Cast<AFPSUILogicCharacter>(HitResult.GetActor()))
			{
				float Distance = FVector::Distance(GetActorLocation(), HitPlayer->GetActorLocation());

				if (Distance < KillArea)
				{
					HitPlayer->CharacterState.GetDamage(9999, GetActorLocation(), GetProjectileOwner(), ProjectileTexture.Get());
				}
				else
				{
					HitPlayer->CharacterState.GetDamage(200/(Distance-KillArea) + 20, GetActorLocation(), GetProjectileOwner(), ProjectileTexture.Get());
				}
			}
		}
	}
	else
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ProjectileSound, GetActorLocation(), FRotator::ZeroRotator, 0.5f, 0.5f, 0, SoundAttenuation);

		if (ExplosionEffect)
		{
			ExplosionEffect->SetWorldRotation(ExplosionRotation);
			ExplosionEffect->Activate();
		}
	}
	
	ServerMeshSetHiddenInGame(false);
	
	GetWorldTimerManager().SetTimer(
		DestroyTimerHandle,
		this,
		&AGrenade::DestroyProjectile,
		2.25f,
		false
	);
}
