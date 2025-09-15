// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class BATTLEROYAL_API AMyActor : public AActor
{
	GENERATED_BODY()


// �Լ�
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
	/// �׳� TotalDamage�� DamageTimeInSeconds�� ������ �Լ�
	/// </summary>
	/// <returns></returns>
	void CalculateValues();

	/*/// <summary>
	/// �� ������ �ǽð����� �ݿ���
	/// </summary>
	/// <param name="PropertyChangedEvent"></param>
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;*/



public :
	// �޽� ����
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Melee;


// ����
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 TotalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageTimeInSeconds;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "Damage")
	float DamagePerSecond;

};
