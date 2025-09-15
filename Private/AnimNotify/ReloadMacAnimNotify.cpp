// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/ReloadMacAnimNotify.h"

#include "Character/FPSWeaponLogicCharacter.h"

void UReloadMacAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (AFPSWeaponLogicCharacter* CurrentCharacter = Cast<AFPSWeaponLogicCharacter>(MeshComp->GetOwner()))
	{
		CurrentCharacter->ReloadAmmo();
	}
}
