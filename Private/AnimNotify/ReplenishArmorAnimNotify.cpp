// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/ReplenishArmorAnimNotify.h"

#include "Character/FPSActionLogicCharacter.h"

void UReplenishArmorAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (AFPSActionLogicCharacter* CurrentCharacter = Cast<AFPSActionLogicCharacter>(MeshComp->GetOwner()))
	{
		CurrentCharacter->ReplenishArmor();
	}
}
