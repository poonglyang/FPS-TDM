// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DamageFeedbackUserWidget.h"

#include "Components/Image.h"
#include "Components/Overlay.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

void UDamageFeedbackUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	
}

void UDamageFeedbackUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}


void UDamageFeedbackUserWidget::SetHitDamageUI(FVector HitPos, FVector ShotPos)
{
	FVector Dir = (ShotPos - HitPos).GetSafeNormal(0.001f);
	
	DamageOverlay->SetRenderTransformAngle(FMath::RadiansToDegrees(FMath::Atan2(Dir.Y, Dir.X)));

	FTimerHandle RemoveTimerHandle;
	GetWorld()->GetTimerManager().SetTimer
	(
		RemoveTimerHandle,
		this,
		&UDamageFeedbackUserWidget::RemoveFromParent,
		2.5f,
		false
	);
}

float UDamageFeedbackUserWidget::CalculateRotationAngle() const
{
	if (!AttackPlayer || !HitPlayer)
		return 0.0f;

	FVector DirVec = (AttackPlayer->GetActorLocation() - HitPlayer->GetActorLocation()).GetSafeNormal2D();

	FVector OwnerForwardVector = HitPlayer->GetActorForwardVector();
	OwnerForwardVector.Z = 0;

	FVector OwnerRightVector = HitPlayer->GetActorRightVector();
	OwnerRightVector.Z = 0;

	// 내적을 이용한 각도
	float Dot = FVector::DotProduct(OwnerForwardVector, DirVec);
	float AngleRad = FMath::Acos(FMath::Clamp(Dot, -1.0f, 1.0f));
	float AngleDeg = FMath::RadiansToDegrees(AngleRad);

	// 시계 방향 여부 판단 (오른쪽 방향을 기준)
	float Dir = FVector::DotProduct(OwnerRightVector, DirVec);
	if (Dir < 0)
	{
		AngleDeg = 360.0f - AngleDeg;
	}

	return AngleDeg;
	
}

void UDamageFeedbackUserWidget::StartHitDamageFeedback(ACharacter* NewAttackPlayer, ACharacter* NewHitPlayer)
{
	AttackPlayer = NewAttackPlayer;
	HitPlayer = NewHitPlayer;

	DamageOverlay->SetRenderTransformAngle(CalculateRotationAngle());
	
	GetWorld()->GetTimerManager().SetTimer
	(
		DamageFeedbackLoopTimerHandle,
		this,
		&UDamageFeedbackUserWidget::LoopHitDamageFeedback,
		LoopTime,
		true
	);
}

void UDamageFeedbackUserWidget::LoopHitDamageFeedback()
{
	ElapsedTime += LoopTime;
	
	if (ElapsedTime >= CollapsedStartTime)
	{
		FLinearColor CurrentDamageImageColor = DamageImage->ColorAndOpacity;
		CurrentDamageImageColor.A = FMath::Clamp(DamageImage->ColorAndOpacity.A - 0.03f, 0.f, 1.f);
		DamageImage->SetColorAndOpacity(CurrentDamageImageColor);

		if (CurrentDamageImageColor.A <= 0 && DamageFeedbackLoopTimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(DamageFeedbackLoopTimerHandle);
			RemoveFromParent();
		}
	}
	else
	{
		DamageOverlay->SetRenderTransformAngle(CalculateRotationAngle());
	}
}





