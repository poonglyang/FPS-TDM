// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AttachArmorAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYAL_API UAttachArmorAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttachArmorAnimNotify")
	TSubclassOf<AActor> ArmorPlateClass;
};
