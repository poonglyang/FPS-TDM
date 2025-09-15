// Fill out your copyright notice in the Description page of Project Settings.


#include "AInteraction.h"

#include "Character/FPSActionLogicCharacter.h"
#include "Controller/FPSActionLogicController.h"

// Sets default values
AAInteraction::AAInteraction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAInteraction::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAInteraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAInteraction::Interaction_Implementation(AFPSActionLogicCharacter* Character)
{
}

