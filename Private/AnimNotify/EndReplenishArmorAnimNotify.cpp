// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/EndReplenishArmorAnimNotify.h"

#include "Character/FPSActionLogicCharacter.h"

void UEndReplenishArmorAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (AFPSActionLogicCharacter* CurrentCharacter = Cast<AFPSActionLogicCharacter>(MeshComp->GetOwner()))
	{
		CurrentCharacter->EndReplenishArmor();
	}
}
