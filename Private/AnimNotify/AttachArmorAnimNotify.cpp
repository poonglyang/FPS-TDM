// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AttachArmorAnimNotify.h"

#include "Character/FPSActionLogicCharacter.h"

void UAttachArmorAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (AFPSActionLogicCharacter* CurrentCharacter = Cast<AFPSActionLogicCharacter>(MeshComp->GetOwner()))
	{
		if (CurrentCharacter->ArmorPlate)
		{
			//CurrentCharacter->SetArmorPlateVisible();
			CurrentCharacter->ArmorPlate->SetActorHiddenInGame(false);
		}
		else
		{
			FActorSpawnParameters SpawnInfo = FActorSpawnParameters();
		
			AActor* SpawnedArmorPlate = MeshComp->GetWorld()->SpawnActor<AActor>(ArmorPlateClass, CurrentCharacter->GetTransform(), SpawnInfo);

			if (!SpawnedArmorPlate)
				return;

			SpawnedArmorPlate->AttachToComponent(MeshComp, FAttachmentTransformRules::KeepRelativeTransform ,FName(TEXT("RightWeaponSocket")));
		
			SpawnedArmorPlate->SetActorRelativeTransform(
				FTransform(
				FRotator(39.859962f,11.423006f, -200.714508f),
				FVector(2.259153f,19.842079f, 0.f)
				)
			);
			CurrentCharacter->ArmorPlate = SpawnedArmorPlate;
		}
		
		
		
	}
}
