// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/FPSBaseController.h"

#include "GameInstance/BaseGameInstance.h"
#include "Net/UnrealNetwork.h"



void AFPSBaseController::BeginPlay()
{
	Super::BeginPlay();

	bAutoManageActiveCameraTarget = false;
}

void AFPSBaseController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSBaseController, bIsCanWork, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSBaseController, bIsPlayerAlive, COND_None, REPNOTIFY_Always);
}

