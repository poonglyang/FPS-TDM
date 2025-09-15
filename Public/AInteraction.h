// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AInteraction.generated.h"

class AFPSActionLogicController;
class AFPSActionLogicCharacter;

UCLASS()
class BATTLEROYAL_API AAInteraction : public AActor
{
	GENERATED_BODY()
	
// constructor
public:	
	// Sets default values for this actor's properties
	AAInteraction();

// function
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AInteraction")
	void Interaction(AFPSActionLogicCharacter* Character);






};
