// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/FPSActionLogicController.h"

#include "Actor/Projectile/BaseProjectile.h"
#include "Character/FPSActionLogicCharacter.h"
#include "GameMode/PlayerLoginGameMode.h"
#include "HUD/TDMHUD.h"
#include "Kismet/GameplayStatics.h"

void AFPSActionLogicController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("AddArmor", IE_Pressed ,this, &AFPSActionLogicController::ReplenishArmor);
	
	InputComponent->BindAction("Interaction", IE_Pressed ,this, &AFPSActionLogicController::Interaction);
	
	InputComponent->BindAction("SelectWeaponUI", IE_Pressed ,this, &AFPSActionLogicController::OpenOrCloseWeaponSelectUI);
	
	InputComponent->BindAction("Tactical", IE_Pressed ,this, &AFPSActionLogicController::UseTacticalItemPressed);
	InputComponent->BindAction("Lethal", IE_Pressed ,this, &AFPSActionLogicController::UseLethalItemPressed);
}

AFPSActionLogicCharacter* AFPSActionLogicController::GetActionLogicCharacter() const
{
	return Cast<AFPSActionLogicCharacter>(GetPawn());
}

void AFPSActionLogicController::ReplenishArmor()
{
	if (!bIsCanWork || !bIsPlayerAlive)
		return;

	if (GetActionLogicCharacter())
	{
		GetActionLogicCharacter()->ServerTryReplenishArmor();
	}
}

void AFPSActionLogicController::UseTacticalItemPressed()
{
	if (GetActionLogicCharacter() && GetTacticalClass())
	{
		GetActionLogicCharacter()->ServerThrowTactical();
	}
}

void AFPSActionLogicController::UseTacticalItemReleased()
{

}

void AFPSActionLogicController::UseLethalItemPressed()
{
	if (GetActionLogicCharacter() && GetLethalClass())
	{
		GetActionLogicCharacter()->ServerThrowLethal();
	}
}

void AFPSActionLogicController::UseLethalItemReleased()
{
	
}

void AFPSActionLogicController::Interaction()
{
	if (!bIsCanWork || !bIsPlayerAlive)
		return;

	if (GetActionLogicCharacter())
	{
		GetActionLogicCharacter()->ServerInteraction();
	}
}

void AFPSActionLogicController::JumpPressed()
{
	if (!bIsPlayerAlive && bIsCanWork)
	{
		ServerRespawn();
		return;
	}
	
	Super::JumpPressed();
}

void AFPSActionLogicController::OpenOrCloseWeaponSelectUI_Implementation()
{
	// if (bIsPlayerAlive)
	// 	return;

	ClientOpenWeaponSelectUI();
}

void AFPSActionLogicController::CloseWeaponSelectUI_Implementation()
{
	
}

void AFPSActionLogicController::ClientOpenWeaponSelectUI()
{
}


void AFPSActionLogicController::ServerRespawn_Implementation()
{
	APlayerLoginGameMode* LoginGameMode = Cast<APlayerLoginGameMode>( UGameplayStatics::GetGameMode(GetWorld()));

	if (!LoginGameMode)
		return;

	LoginGameMode->RespawnPlayer(this);
	bIsPlayerAlive = true;

	ClientRespawn();
}

void AFPSActionLogicController::ClientRespawn_Implementation()
{
	ATDMHUD* CurrentHUD = Cast<ATDMHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->OwnerRespawn();
}

