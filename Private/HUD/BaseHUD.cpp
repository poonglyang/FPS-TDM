// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BaseHUD.h"

#include "Blueprint/WidgetLayoutLibrary.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());

	
}
