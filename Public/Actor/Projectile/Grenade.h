// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Projectile/BaseProjectile.h"
#include "Grenade.generated.h"

/**
 * 
 */
class UNiagaraComponent;
UCLASS()
class BATTLEROYAL_API AGrenade : public ABaseProjectile
{
	GENERATED_BODY()

	AGrenade();

public:
	virtual void SetProjectileOwner(AFPSUILogicController* NewOwnerController) override;
	
protected:
	virtual void ProjectileAction() override;

	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grenade")
	UNiagaraComponent* ExplosionEffect;

	FRotator ExplosionRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grenade")
	float GrenadeArea = 600;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grenade")
	float KillArea = 400;

	UPROPERTY()
	FTimerHandle DestroyTimerHandle;
};
