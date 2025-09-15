// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ThrowProjectileAnimNotify.generated.h"

class ABaseProjectile;
/**
 * 
 */
UCLASS()
class BATTLEROYAL_API UThrowProjectileAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	bool bIsLethal = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FName ThrowSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ProjectileSpeed = 8000.f;
};
