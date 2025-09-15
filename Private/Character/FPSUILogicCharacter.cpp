// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FPSUILogicCharacter.h"

#include "Components/WidgetComponent.h"
#include "Controller/FPSUILogicController.h"
#include "Net/UnrealNetwork.h"

AFPSUILogicCharacter::AFPSUILogicCharacter()
{
	DiscriminationWidget = CreateDefaultSubobject<UWidgetComponent>("DiscriminationWidget");
	DiscriminationWidget->SetupAttachment(RootComponent);

	DiscriminationWidget->SetRelativeLocation(FVector(0,0,100));
}

void AFPSUILogicCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSUILogicCharacter, TeamNum, COND_None, REPNOTIFY_Always);
}

void AFPSUILogicCharacter::BeginPlay()
{
	Super::BeginPlay();
	CharacterCarryAmmo.SetOwner(this);
}

void AFPSUILogicCharacter::OnRep_TeamNum()
{
	AFPSUILogicController* CurrentController = Cast<AFPSUILogicController>(GetController());
	if ( !CurrentController)
		return;

	CurrentController->ServerUpdateFriendIdentification();
}

void AFPSUILogicCharacter::SetCharacterTeamNum(int32 NewTeamNum)
{
	TeamNum = NewTeamNum;
}

int AFPSUILogicCharacter::GetCharacterTeamNum() const
{
	return TeamNum;
}
