// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.h"
#include "WorldMoveArea.generated.h"

UCLASS()
class BATTLEROYAL_API AWorldMoveArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldMoveArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ������
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

	/// <summary>
	/// ���Ͱ� ������ �� ���Ͱ� �÷��̾� ĳ���͸� �߰�
	/// </summary>
	/// <param name="Player"></param>
	UFUNCTION(BlueprintCallable)
	void PlayerBeginOverlap(AActor* OtherActor);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/// <summary>
	/// ���Ͱ� ������ �� ���Ͱ� �÷��̾� ĳ���͸� ����
	/// </summary>
	/// <param name="Player"></param>
	UFUNCTION(BlueprintCallable)
	void PlayerEndOverlap(AActor* OtherActor);

	/// <summary>
	/// ���� �÷��̾� �迭�� �ִ� ���� ���� ����Ʈ �ϴ� �Լ�
	/// </summary>
	UFUNCTION()
	void PrintPlayerArr();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void SetMoveAreaTextRenderText(const FString& text);

	UFUNCTION(BlueprintImplementableEvent)
	void GameStartCountdown();

public:
	// �޽�
	UPROPERTY()
	class UStaticMeshComponent* Cube;
	
	// �޽� ���͸���
	UPROPERTY(VisibleInstanceOnly)
	UMaterialInterface* CubeMaterial = nullptr;

	// �÷��̾ Ž���� �ݸ���
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category=WorldMove)
	class UBoxComponent* DetectedCollision;

	// �÷��̾� ĳ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = WorldMove)
	TArray<ABaseCharacter*> PlayerArr;

	/// <summary>
	/// ���� ���� ���� TextRender
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = WorldMove)
	class UTextRenderComponent* MoveAreaTextRender;


	/// <summary>
	/// MoveAreaText�� ���� ����
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = WorldMove)
	FString TextRenderText;
};
