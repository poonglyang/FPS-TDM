// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BasePC.h"

void ACPP_BasePC::PawnLeavingGame()
{
	Super::PawnLeavingGame();

	/*UE_LOG(LogTemp, Display, TEXT("PawnLeavingGame Overrie Func Execution"));
	if (GetPawn() != NULL)
	{
		UE_LOG(LogTemp, Display, TEXT("Pawn Unpossess"));
		UnPossess();
		SetPawn(NULL);
	}*/
}

void ACPP_BasePC::ClientTravelFucntion(FString levelAddress)
{
	if (HasAuthority()) {
		this->ClientTravel(levelAddress, ETravelType::TRAVEL_Absolute); 
	}
}

