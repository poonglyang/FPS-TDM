// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/FPSWeaponLogicCharacter.h"
#include "FPSActionLogicCharacter.generated.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(LOG_FPSActionLogicCharacter, Log, All);

class ABaseWeapon;

UCLASS()
class BATTLEROYAL_API AFPSActionLogicCharacter : public AFPSWeaponLogicCharacter
{
	GENERATED_BODY()
protected:
	AFPSActionLogicCharacter();

	virtual void BeginPlay() override;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	// ---------------------- 방어구 채우기 --------------------
	UFUNCTION(Server, Reliable)
	void ServerTryReplenishArmor();

	UFUNCTION(NetMulticast, Reliable)
	void MultiTryReplenishArmor();

	UFUNCTION()
	void TryReplenishArmor();

	UFUNCTION(Server, Reliable)
	void ServerEndReplenishArmor();

	UFUNCTION(NetMulticast, Reliable)
	void MultiEndReplenishArmor();

	UFUNCTION()
	void EndReplenishArmor();

	UFUNCTION()
	void ReplenishArmor();
	// ---------------------- 방어구 채우기 End ----------------

	// ---------------------- 상호작용 ------------------------
	UFUNCTION(Server, Reliable)
	void ServerInteraction();

	UFUNCTION()
	virtual void GetWeapon(ABaseWeapon* DetectedWeapon);
	// ---------------------- 상호작용 End --------------------

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "PlayerDeath")
	void ServerPlayerDeath(FVector AttackLocation);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "PlayerDeath")
	void MultiPlayerDeath();

	// --------------------- 레그돌 ---------------------------
	
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "PlayerDeath")
	void ServerRagdoll(FVector AttackLocation);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "PlayerDeath")
	void MultiRagdoll(FVector AttackLocation);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "PlayerDeath")
	void Ragdoll(FVector AttackLocation);

	// --------------------- 레그돌 End ------------------------

	// --------------------- 투척류 ----------------------------
	
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Projectile")
	void ServerThrowTactical();
	
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "Projectile")
	void MultiThrowTactical();

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Projectile")
	void ServerThrowLethal();
	
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "Projectile")
	void MultiThrowLethal();
	

	// --------------------- 투척류 End ------------------------

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "ArmorPlate")
	void MultiSetArmorPlateVisible();
	
	void SetArmorPlateVisible();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "ArmorPlate")
	void MultiSetArmorPlateHidden();
	
	void SetArmorPlateHidden();

	
	
	void DestroyCharacter();

	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerState")
	float MaxArmorValue = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerState")
	float InteractionRadius = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerState")
	float InteractionHalfHeight = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerState")
	float RagDollStrength = 500.f;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "PlayerState")
	AActor* ArmorPlate;
};
