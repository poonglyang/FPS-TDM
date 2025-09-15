// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/WeaponSetVisiblityAnimNotify.h"

#include "Character/FPSUILogicCharacter.h"

void UWeaponSetVisiblityAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp->GetOwner() && MeshComp->GetOwner()->HasAuthority())
	{
		AFPSUILogicCharacter* CurrentCharacter = Cast<AFPSUILogicCharacter>(MeshComp->GetOwner());\
		if (CurrentCharacter)
			CurrentCharacter->CurrentWeaponHidden(bIsWeaponHidden);
	}
}
