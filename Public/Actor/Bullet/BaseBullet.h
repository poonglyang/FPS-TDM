// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBullet.generated.h"

class AFPSUILogicController;
class UProjectileMovementComponent;
class UTexture2D;
class USphereComponent;

UCLASS()
class BATTLEROYAL_API ABaseBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void DestroyBullet();
	
public:
	UFUNCTION(BlueprintCallable, Category = "Bullet")
	virtual void SetBulletDamage(float HeadDamage, float BodyDamage, float ArmDamage, float HandDamage, float LegDamage, float FootDamage);

protected:
	UFUNCTION()
	void BulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	TArray<FHitResult> SortActors(TArray<FHitResult>& OutHits, FVector StartLocation);
public:
	/**
	 * \brief 총알 속도
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet", meta=(ExposeOnSpawn=true))
	float BulletSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet")
	USphereComponent* BulletCollision;

	/**
	 * \brief 태그와 태그에 따른 총기 데미지
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet")
	TMap<FName, float> BulletDamageMap;

	/**
	 * \brief 총을 발사한 지점
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	FVector FirePoint;

	/**
	 * \brief 총을 쏜 사람
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet", meta=(ExposeOnSpawn=true))
	ACharacter* Shotter;

	/**
 * \brief 총을 쏜 사람
 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet", meta=(ExposeOnSpawn=true))
	AFPSUILogicController* ShotterController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet", meta=(ExposeOnSpawn=true))
	UTexture2D* ShotWeaponTexture;

	/**
	 * \brief 총알의 방향
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	FVector BulletVelocity;

	/**
	 * \brief 총알 현재 틱 위치 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	FVector CurrentPos;

	/**
	 * \brief 총알 다음 틱 위치
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	FVector NextPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float Gravity = 980;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float FiscalMultiplier = 10;
};
