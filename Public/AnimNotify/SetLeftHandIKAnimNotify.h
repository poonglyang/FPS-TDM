// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SetLeftHandIKAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYAL_API USetLeftHandIKAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	bool bUseLeftHandIk = true;
};
