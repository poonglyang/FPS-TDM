// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "WeaponSetVisiblityAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYAL_API UWeaponSetVisiblityAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	bool bIsWeaponHidden = true;
};
