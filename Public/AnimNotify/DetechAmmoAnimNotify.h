// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DetechAmmoAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYAL_API UDetechAmmoAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

	protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
