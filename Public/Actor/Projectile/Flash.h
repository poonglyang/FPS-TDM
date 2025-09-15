// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Projectile/BaseProjectile.h"
#include "Flash.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYAL_API AFlash : public ABaseProjectile
{
	GENERATED_BODY()

protected:
	virtual void ProjectileAction() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flash")
	float FlashArea = 600;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flash")
	USoundBase* FlashSound;
	
	UPROPERTY()
	FTimerHandle DestroyTimerHandle;
};
