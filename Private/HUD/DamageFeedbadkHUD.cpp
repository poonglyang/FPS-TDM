// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/DamageFeedbadkHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/DamageFeedbackUserWidget.h"
#include "UI/HitArmorUserWidget.h"
#include "UI/HitEffectUserWidget.h"

void ADamageFeedbadkHUD::BeginPlay()
{
	Super::BeginPlay();

	CreateHitEffectWidget();
	CreateHitArmorWidget();
}


void ADamageFeedbadkHUD::CreateHitEffectWidget()
{
	if (HitEffectUserWidget)
	{
		UE_LOG(LOG_PlayerMainHUD, Warning, TEXT("HitEffectUserWidget은 이미 만들어져 있습니다"));
		return;
	}
	
	HitEffectUserWidget = Cast<UHitEffectUserWidget>(CreateWidget(GetOwningPlayerController(), HitEffectUserWidgetClass));

	if (!HitEffectUserWidget)
	{
		UE_LOG(LOG_PlayerMainHUD, Error, TEXT("HitEffectUserWidget이게 우에 일어납니까...?"));
		return;
	}

	HitEffectUserWidget->AddToViewport();
}

void ADamageFeedbadkHUD::CreateHitArmorWidget()
{
	if (HitArmorUserWidget)
	{
		UE_LOG(LOG_PlayerMainHUD, Warning, TEXT("HitArmorUserWidget은 이미 만들어져 있습니다"));
		return;
	}
	
	HitArmorUserWidget = Cast<UHitArmorUserWidget>(CreateWidget(GetOwningPlayerController(), HitArmorUserWidgetClass));

	if (!HitArmorUserWidget)
	{
		UE_LOG(LOG_PlayerMainHUD, Error, TEXT("HitArmorUserWidget이게 우에 일어납니까...?"));
		return;
	}

	HitArmorUserWidget->AddToViewport();
}

UDamageFeedbackUserWidget* ADamageFeedbadkHUD::CreateDamageFeedbackWidget()
{
	UDamageFeedbackUserWidget* DamageFeedbackUserWidget = Cast<UDamageFeedbackUserWidget>(CreateWidget(GetOwningPlayerController(), DamageFeedbackUserWidgetClass));

	if (!DamageFeedbackUserWidget)
	{
		UE_LOG(LOG_PlayerMainHUD, Error, TEXT("UDamageFeedbackUserWidget이게 우에 일어납니까...?"));
		return nullptr;
	}

	DamageFeedbackUserWidget->AddToViewport();

	return DamageFeedbackUserWidget;
}

void ADamageFeedbadkHUD::SetHitEffect(bool bIsKill)
{
	if (!HitEffectUserWidget)
	{
		CreateHitEffectWidget();
		//SetHitEffect(bIsKill);
		return;
	}
	HitEffectUserWidget->SetVisible(bIsKill);
}

void ADamageFeedbadkHUD::SetHitArmor(bool bIsCrush)
{
	if (!HitArmorUserWidget)
	{
		CreateHitEffectWidget();
		//SetHitArmor(bIsCrush);
		return;
	}
	HitArmorUserWidget->SetArmorEffectVisible(bIsCrush);
}

void ADamageFeedbadkHUD::SetDamageFeedback(FVector HitPos, FVector ShotPos)
{
	UDamageFeedbackUserWidget* DamageFeedbackUserWidget = CreateDamageFeedbackWidget();
	if (!DamageFeedbackUserWidget)
		return;
	
	DamageFeedbackUserWidget->SetHitDamageUI(HitPos, ShotPos);
}

void ADamageFeedbadkHUD::SetDynamicDamageFeedback(ACharacter* NewAttackPlayer, ACharacter* NewHitPlayer)
{
	UDamageFeedbackUserWidget* DamageFeedbackUserWidget = CreateDamageFeedbackWidget();
	if (!DamageFeedbackUserWidget)
		return;
	
	DamageFeedbackUserWidget->StartHitDamageFeedback(NewAttackPlayer, NewHitPlayer);
}





