// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "FuckTestSkeletalMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYAL_API UFuckTestSkeletalMeshComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

protected:
	virtual bool ShouldCreatePhysicsState() const override;
	
	//virtual void OnCreatePhysicsState() override;
};
