// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Projectile/Flash.h"

#include "Character/FPSUILogicCharacter.h"
#include "Controller/FPSUILogicController.h"
#include "Kismet/GameplayStatics.h"


void AFlash::ProjectileAction()
{
	Super::ProjectileAction();
	

	if (HasAuthority())
	{
		TArray<FHitResult> HitResults;
		
		DetectedPlayer(HitResults,GetActorLocation() ,GetActorLocation(), FlashArea);
	
		for (FHitResult HitResult : HitResults)
		{
			if (AFPSUILogicCharacter* HitPlayer = Cast<AFPSUILogicCharacter>(HitResult.GetActor()))
			{
				float Distance = FVector::Distance(HitPlayer->GetActorLocation(), GetActorLocation());
				
				if (AFPSUILogicController* HitPlayerController =  Cast<AFPSUILogicController>( HitPlayer->GetController()))
				{
					HitPlayerController->ClientFlashHitEffect(Distance / FlashArea, FlashSound);
				}
			}
		}
	}
	else
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ProjectileSound, GetActorLocation(), FRotator::ZeroRotator, 0.5f, 0.5f, 0, SoundAttenuation);
	}

	ServerMeshSetHiddenInGame(false);
	
	GetWorldTimerManager().SetTimer(
		DestroyTimerHandle,
		this,
		&AFlash::DestroyProjectile,
		2.25f,
		false
	);
}
