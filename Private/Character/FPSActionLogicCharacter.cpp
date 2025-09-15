// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FPSActionLogicCharacter.h"

#include "AInteraction.h"
#include "Actor/Weapon/BaseWeapon.h"
#include "Controller/FPSActionLogicController.h"
#include "Controller/FPSUILogicController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LOG_FPSActionLogicCharacter);

AFPSActionLogicCharacter::AFPSActionLogicCharacter()
{
	
}

void AFPSActionLogicCharacter::BeginPlay()
{
	Super::BeginPlay();
	CharacterState.SetOwnerCharacter(this);
}

void AFPSActionLogicCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(AFPSActionLogicCharacter, ArmorPlate, COND_None, REPNOTIFY_Always);
}


void AFPSActionLogicCharacter::ServerTryReplenishArmor_Implementation()
{
	if (CharacterState.GetArmor() == CharacterState.GetMaxArmor() || !bCanAttack)	// 아머가 최대치거나 공격 가능이 아니면
		return;

	MultiTryReplenishArmor();
	MultiMontagePlayWithSession(UpperBodyMontage, FName(TEXT("EquipPlate")));
}

void AFPSActionLogicCharacter::MultiTryReplenishArmor_Implementation()
{
	TryReplenishArmor();
}


void AFPSActionLogicCharacter::TryReplenishArmor()
{
	bUseLeftHandIK = false;
	bCanAttack = false;
	CurrentWeaponHidden(true);
}

void AFPSActionLogicCharacter::ServerEndReplenishArmor_Implementation()
{
	MultiEndReplenishArmor();
}

void AFPSActionLogicCharacter::MultiEndReplenishArmor_Implementation()
{
	EndReplenishArmor();
}

void AFPSActionLogicCharacter::EndReplenishArmor()
{
	bUseLeftHandIK = true;
	bCanAttack = true;
	CurrentWeaponHidden(false);
}

void AFPSActionLogicCharacter::ReplenishArmor()
{
	if (HasAuthority())
	{
		CharacterState.SetArmor(CharacterState.GetArmor() + 33.4f);
	}
}

void AFPSActionLogicCharacter::ServerInteraction_Implementation()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> InteractionObjectTypes;
	InteractionObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1));
	InteractionObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel3));
	
	TArray<AActor*> IgnoreActorArr;

	AActor* CurrentWeaponActor = Cast<AActor>(CurrentWeapon);
	if (CurrentWeaponActor) 
		IgnoreActorArr.Add(CurrentWeaponActor);

	AActor* MainWeaponActor = Cast<AActor>(MainWeapon);
	if (MainWeaponActor)
		IgnoreActorArr.Add(MainWeaponActor);

	AActor* SubWeaponActor = Cast<AActor>(SubWeapon);
	if (SubWeaponActor)
		IgnoreActorArr.Add(SubWeaponActor);
		
	FHitResult OutHit;

	if (!CurrentCamera)
	{
		UE_LOG(LOG_FPSActionLogicCharacter, Error, TEXT("카메라가 없음"));
		return;
	}
	
	if (
		!UKismetSystemLibrary::CapsuleTraceSingleForObjects(
			GetWorld(),
			GetMesh()->GetSocketLocation(FName(TEXT("headSocket"))),
			GetMesh()->GetSocketLocation(FName(TEXT("headSocket"))) + CurrentCamera->GetForwardVector() * 200.0f,
			InteractionRadius,
			InteractionHalfHeight,
			InteractionObjectTypes,
			false,
			IgnoreActorArr,
			EDrawDebugTrace::None,
			OutHit,
			true
		)
	)
		return ;

	if (ABaseWeapon* HitWeapon = Cast<ABaseWeapon>(OutHit.Actor))
	{
		GetWeapon(HitWeapon);
		return;
	}

	if (AAInteraction* HitInteraction = Cast<AAInteraction>(OutHit.Actor))
	{
		HitInteraction->Interaction(this);
	}
	
}

void AFPSActionLogicCharacter::GetWeapon(ABaseWeapon* DetectedWeapon)
{
	if (DetectedWeapon->GetAttachParentActor())
		return; // 감지된 총에 부모가 있으면 (누군가 들고 있는 것이면)

	if (CurrentWeapon)
	{
		// 지금 손에 들고 있는 무기가 있고
		if (MainWeapon)
		{
			// 지금 손에 들고 있는 무기가 있고 1번 무기가 있으면
			if (SubWeapon)
			{
				// 지금 손에 들고 있는 무기가 있고 1번 무기가 있으면서 2번 무기가 있으면
				CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

				TArray<TEnumAsByte<EObjectTypeQuery>> DropAbleObjectTypes;

				TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
				DropAbleObjectTypes.Add(WorldStatic);
				DropAbleObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel2));

				TArray<AActor*> IgnoreActorArr;

				FHitResult OutHit;
				
				if (
					!UKismetSystemLibrary::LineTraceSingleForObjects(
						GetWorld(),
						GetActorLocation(),
						GetActorUpVector() * -10000 + GetActorLocation(),
						DropAbleObjectTypes,
						false,
						IgnoreActorArr,
						EDrawDebugTrace::None,
						OutHit,
						true
					)
				)
				{
					UE_LOG(LOG_FPSActionLogicCharacter, Error, TEXT("플레이어 하단에 -10000의 길이 동안 바닥이 없다고요?"));
					return;
				}

				CurrentWeapon->SetActorLocation(OutHit.ImpactPoint + FVector(0,100,0));
				CurrentWeapon->SetActorRotation(FRotator(-90,0,0));
				
				if (CurrentWeapon == MainWeapon)
				{
					MainWeapon = DetectedWeapon;
					CurrentWeapon = MainWeapon;
				}
				else
				{
					SubWeapon = DetectedWeapon;
					CurrentWeapon = DetectedWeapon;
				}
					
			}
			else
			{
				// 지금 손에 들고 있는 무기가 있고 1번 무기가 있으면서 2번 무기는 없으면
				SubWeapon = DetectedWeapon;
				SubWeapon->SetActorHiddenInGame(true);
				SubWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,FName(TEXT("RightWeaponSocket")));

				if (DetectedWeapon->DestroyTimer.IsValid())
					GetWorldTimerManager().ClearTimer(DetectedWeapon->DestroyTimer);
				
			}
		}
		else
		{
			
			// 1번 무기가 없으면
			MainWeapon = DetectedWeapon;
			MainWeapon->SetActorHiddenInGame(true);
			
			CurrentWeapon->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules(
				EAttachmentRule::KeepRelative, true),
				FName(TEXT("RightWeaponSocket")
				)
			);
			
			if (DetectedWeapon->DestroyTimer.IsValid())
				GetWorldTimerManager().ClearTimer(DetectedWeapon->DestroyTimer);
		}
	}
	else
	{
		// 지금 손에 들고 있는 무기가 없고
		if (MainWeapon)
		{
			// 지금 손에 들고 있는 무기가 없고 1번 무기는 있으면
			if (!SubWeapon)
			{
				UE_LOG(LOG_FPSActionLogicCharacter, Error, TEXT("장착된 무기가 없고 1번이 있는데 2번이 없는건 불가능 합니다"));
				return;
			}

			CurrentWeapon = SubWeapon = DetectedWeapon;
		}
		else
		{
			// 지금 손에 들고 있는 무기가 없고 1번 무기도 없으면
			CurrentWeapon = MainWeapon = DetectedWeapon;
		}
	}

	if (GetMesh()->DoesSocketExist(FName(TEXT("RightWeaponSocket"))))
	{
		UE_LOG(LOG_FPSActionLogicCharacter, Log, TEXT("해당 소켓 있음"));
	}
	else
	{
		UE_LOG(LOG_FPSActionLogicCharacter, Error, TEXT("해당 소켓 없음?????"));
	}

	CurrentWeapon->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules(
				EAttachmentRule::KeepRelative, true),
				FName(TEXT("RightWeaponSocket")
				)
			);

	CurrentWeapon->SetActorRelativeTransform(CurrentWeapon->GetRightHandTransform());
	
	UE_LOG(LOG_FPSActionLogicCharacter, Log, TEXT("%s"),*CurrentWeapon->GetAttachParentSocketName().ToString());
	
	PlayerEquipWeaponType = CurrentWeapon->WeaponEquipType;
	
	bIsWeaponEquip = true;

	if (DetectedWeapon->DestroyTimer.IsValid())
		GetWorldTimerManager().ClearTimer(DetectedWeapon->DestroyTimer);

	if (AFPSUILogicController* CurrentController =  Cast<AFPSUILogicController>(GetController()))
	{
		CurrentController->ClientUpdateWeaponIconUI(CurrentWeapon->GetIcon());
		CurrentController->ClientUpdateWeaponAmmoUI(CurrentWeapon->GetCurrentAmmoCount());
		CurrentController->ClientUpdateCharacterCarryAmmo(CharacterCarryAmmo.GetWeaponCarryAmmo(CurrentWeapon->WeaponType));
	}
}



void AFPSActionLogicCharacter::ServerPlayerDeath_Implementation(FVector AttackLocation)
{
	ServerRagdoll(AttackLocation);
	MultiPlayerDeath();

	if (CurrentWeapon)
	{
		CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		TArray<TEnumAsByte<EObjectTypeQuery>> DropAbleObjectTypes;

		TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
		DropAbleObjectTypes.Add(WorldStatic);
		DropAbleObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel2));

		TArray<AActor*> IgnoreActorArr;

		FHitResult OutHit;
				
		if (
			!UKismetSystemLibrary::LineTraceSingleForObjects(
				GetWorld(),
				GetActorLocation(),
				GetActorUpVector() * -10000 + GetActorLocation(),
				DropAbleObjectTypes,
				false,
				IgnoreActorArr,
				EDrawDebugTrace::None,
				OutHit,
				true
			)
		)
		{
			UE_LOG(LOG_FPSActionLogicCharacter, Error, TEXT("플레이어 하단에 -10000의 길이 동안 바닥이 없다고요?"));
			return;
		}

		CurrentWeapon->SetActorLocation(OutHit.ImpactPoint + FVector(0,100,0));
		CurrentWeapon->SetActorRotation(FRotator(-90,0,0));

		if (CurrentWeapon == MainWeapon)
		{
			if (SubWeapon)
				SubWeapon->Destroy();
		}
		else
		{
			if (MainWeapon)
				MainWeapon->Destroy();
		}

		CurrentWeapon = nullptr;

	}
	

	
	FTimerHandle PlayerDeathTimerHandle;
	
	GetWorldTimerManager().ClearAllTimersForObject(this);

	if (HealthRegenTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(HealthRegenTimerHandle); 
	}
	if (HealTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(HealTimerHandle); 
	}
	
	GetWorldTimerManager().SetTimer(
		PlayerDeathTimerHandle,
		this,
		&AFPSActionLogicCharacter::DestroyCharacter,
		3.f,
		false
	);
}

void AFPSActionLogicCharacter::MultiPlayerDeath_Implementation()
{
	if (!CurrentCamera || !DeathCamera)
		return;

	DeathCamera->SetRelativeTransform(CurrentCamera->GetRelativeTransform());

	APlayerController* CurrentPlayerController = Cast<APlayerController>( GetController());
	if (!CurrentPlayerController)
		return;

	CurrentPlayerController->SetViewTargetWithBlend(DeathCamera->GetChildActor());

	GetWorldTimerManager().ClearAllTimersForObject(this);

	if (HealthRegenTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(HealthRegenTimerHandle); 
	}
	if (HealTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(HealTimerHandle); 
	}
}

void AFPSActionLogicCharacter::ServerRagdoll_Implementation(FVector AttackLocation)
{
	MultiRagdoll(AttackLocation);
}

void AFPSActionLogicCharacter::MultiRagdoll_Implementation(FVector AttackLocation)
{
	Ragdoll(AttackLocation);
}

void AFPSActionLogicCharacter::Ragdoll_Implementation(FVector AttackLocation)
{
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);

	FVector ImpulseDirection = (GetActorLocation() - AttackLocation).GetSafeNormal() * RagDollStrength;
	
	GetMesh()->SetPhysicsLinearVelocity(FVector::ZeroVector);
	GetMesh()->AddImpulseToAllBodiesBelow(ImpulseDirection, NAME_None);
}

void AFPSActionLogicCharacter::ServerThrowTactical_Implementation()
{
	if (CharacterCarryAmmo.GetTacticalProjectile() <= 0)
		return;
	
	MultiThrowTactical();
}

void AFPSActionLogicCharacter::MultiThrowTactical_Implementation()
{
	PlayMontageWithSession(UpperBodyMontage, FName(TEXT("ThrowFlash")));
}

void AFPSActionLogicCharacter::ServerThrowLethal_Implementation()
{
	if (CharacterCarryAmmo.GetLethalProjectile() <= 0)
		return;
	
	MultiThrowLethal();
}

void AFPSActionLogicCharacter::MultiThrowLethal_Implementation()
{
	PlayMontageWithSession(UpperBodyMontage, FName(TEXT("ThrowFrag")), 0.7f);
}

void AFPSActionLogicCharacter::MultiSetArmorPlateVisible_Implementation()
{
	SetArmorPlateVisible();
}

void AFPSActionLogicCharacter::MultiSetArmorPlateHidden_Implementation()
{
	SetArmorPlateHidden();
}

void AFPSActionLogicCharacter::SetArmorPlateVisible()
{
	if (ArmorPlate)
	{
		TArray<USceneComponent*> ArmorPlateComponents = ArmorPlate->GetRootComponent()->GetAttachChildren();
		for (USceneComponent* ArmorPlateComponent : ArmorPlateComponents)
		{
			UStaticMeshComponent* ArmorPlateMesh = Cast<UStaticMeshComponent>(ArmorPlateComponent);
			ArmorPlateMesh->SetVisibility(true);
		}
	}
}

void AFPSActionLogicCharacter::SetArmorPlateHidden()
{
	if (ArmorPlate)
	{
		TArray<USceneComponent*> ArmorPlateComponents = ArmorPlate->GetRootComponent()->GetAttachChildren();
		for (USceneComponent* ArmorPlateComponent : ArmorPlateComponents)
		{
			UStaticMeshComponent* ArmorPlateMesh = Cast<UStaticMeshComponent>(ArmorPlateComponent);
			ArmorPlateMesh->SetVisibility(false);
		}
	}
}

void AFPSActionLogicCharacter::DestroyCharacter()
{
	Destroy();
}
