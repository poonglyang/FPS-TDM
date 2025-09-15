// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <queue>

#include "CoreMinimal.h"
#include "AInteraction.h"
#include "AmmoBox.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYAL_API AAmmoBox : public AAInteraction
{
	GENERATED_BODY()
protected:
	AAmmoBox();

	virtual void Interaction_Implementation(AFPSActionLogicCharacter* Character) override;

	void UseCoolTimerDown();
	
protected:
	/// <summary>
	/// Mesh
	/// </summary>
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Ammobox;

	UPROPERTY(VisibleAnywhere)
	TArray<AFPSActionLogicCharacter*> UseCharacterArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AmmoBox")
	float CoolTime = 15.f;
};
