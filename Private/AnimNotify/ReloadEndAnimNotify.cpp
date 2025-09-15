// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/ReloadEndAnimNotify.h"

#include "Character/FPSWeaponLogicCharacter.h"

void UReloadEndAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (AFPSWeaponLogicCharacter* CurrentCharacter = Cast<AFPSWeaponLogicCharacter>(MeshComp->GetOwner()))
	{
		CurrentCharacter->SetUseLeftHandIK(true);
		CurrentCharacter->SetCanAttack(true);
	}
}
