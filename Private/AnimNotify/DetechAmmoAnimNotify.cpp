// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/DetechAmmoAnimNotify.h"

#include "Character/FPSActionLogicCharacter.h"

void UDetechAmmoAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);


	if (AFPSActionLogicCharacter* CurrentCharacter = Cast<AFPSActionLogicCharacter>(MeshComp->GetOwner()))
	{
		if (!CurrentCharacter->ArmorPlate)
			return;

		//CurrentCharacter->ArmorPlate->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		//CurrentCharacter->ArmorPlate->Destroy();
		//CurrentCharacter->SetArmorPlateVisible();
		CurrentCharacter->ArmorPlate->SetActorHiddenInGame(true);
		//CurrentCharacter->ArmorPlate = nullptr;
	}
}
