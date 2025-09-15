// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

class AFPSUILogicController;
class UCapsuleComponent;

UCLASS()
class BATTLEROYAL_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	virtual void SetProjectileOwner(AFPSUILogicController* NewOwnerController);

	UFUNCTION()
	void OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	AFPSUILogicController* GetProjectileOwner();
	
	UFUNCTION()
	virtual void ProjectileAction();
	
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	virtual void DetectedPlayer(TArray<FHitResult>& HitResults, FVector StartLoc, FVector EndLoc, float Radius);

	virtual void DestroyProjectile();

	UFUNCTION(Server, Reliable, Category = "Projectile")
	virtual void ServerMeshSetHiddenInGame(bool bIsHidden);

	UFUNCTION(NetMulticast, Reliable, Category = "Projectile")
	virtual void MultiMeshSetHiddenInGame(bool bIsHidden);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileBase")
	UCapsuleComponent* Collision;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileBase")
	UMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "ProjectileBase", meta=(ExposeOnSpawn=true))
	AFPSUILogicController* OwnerPlayer;
	
	UPROPERTY(VisibleAnywhere ,Category = "ProjectileBase")
	FTimerHandle ProjectileActionTimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileBase")
	float ProjectileActionCoolTime = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileBase")
	TSoftObjectPtr<UTexture2D> ProjectileTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileBase")
	USoundBase* ProjectileSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileBase")
	USoundAttenuation* SoundAttenuation;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileBase")
	float LinearDampingMultiplier = 1.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileBase")
	float AngularDampingMultiplier = 1.5f;


};
