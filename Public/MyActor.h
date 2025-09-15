// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class BATTLEROYAL_API AMyActor : public AActor
{
	GENERATED_BODY()


// 함수
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitProperties() override;

	/// <summary>
	/// 그냥 TotalDamage와 DamageTimeInSeconds를 나누는 함수
	/// </summary>
	/// <returns></returns>
	void CalculateValues();

	/*/// <summary>
	/// 값 변경을 실시간으로 반영함
	/// </summary>
	/// <param name="PropertyChangedEvent"></param>
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;*/



public :
	// 메시 변수
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Melee;


// 변수
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 TotalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageTimeInSeconds;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "Damage")
	float DamagePerSecond;

};
