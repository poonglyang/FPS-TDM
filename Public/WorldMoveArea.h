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

	// 오버랩
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

	/// <summary>
	/// 액터가 들어왔을 때 액터가 플레이어 캐릭터면 추가
	/// </summary>
	/// <param name="Player"></param>
	UFUNCTION(BlueprintCallable)
	void PlayerBeginOverlap(AActor* OtherActor);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/// <summary>
	/// 액터가 나갔을 때 액터가 플레이어 캐릭터면 삭제
	/// </summary>
	/// <param name="Player"></param>
	UFUNCTION(BlueprintCallable)
	void PlayerEndOverlap(AActor* OtherActor);

	/// <summary>
	/// 그저 플레이어 배열에 있는 것을 전부 프린트 하는 함수
	/// </summary>
	UFUNCTION()
	void PrintPlayerArr();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void SetMoveAreaTextRenderText(const FString& text);

	UFUNCTION(BlueprintImplementableEvent)
	void GameStartCountdown();

public:
	// 메시
	UPROPERTY()
	class UStaticMeshComponent* Cube;
	
	// 메시 머터리얼
	UPROPERTY(VisibleInstanceOnly)
	UMaterialInterface* CubeMaterial = nullptr;

	// 플레이어를 탐지할 콜리전
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category=WorldMove)
	class UBoxComponent* DetectedCollision;

	// 플레이어 캐릭터 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = WorldMove)
	TArray<ABaseCharacter*> PlayerArr;

	/// <summary>
	/// 발판 위에 있을 TextRender
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = WorldMove)
	class UTextRenderComponent* MoveAreaTextRender;


	/// <summary>
	/// MoveAreaText에 적을 문구
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = WorldMove)
	FString TextRenderText;
};
