// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/FPSBaseController.h"
#include "FPSMovementLogicController.generated.h"

class AFPSMovementLogicCharacter;
/**
 * 
 */

UCLASS()
class BATTLEROYAL_API AFPSMovementLogicController : public AFPSBaseController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;
	
	/**
	 * \brief 마우스 좌우
	 * \param AxisValue 
	 */
	void Turn(const float AxisValue);

	/**
	 * \brief 마우스 위 아래
	 * \param AxisValue 
	 */
	void LookUp(const float AxisValue);
	
	/**
	 * \brief Get AFPSMovementLogicCharacter to GetPawn()
	 * \return Current Possess AFPSMovementLogicCharacter
	 */
	AFPSMovementLogicCharacter* GetMovementLogicCharacter() const;
	
	/**
	 * \brief 앞뒤로 이동하는 함수 (플레이어 캐릭터의 앞뒤 이동 함수를 불러온다)
	 * \param AxisValue 값
	 */
	virtual void MoveForward(const float AxisValue);

	/**
	 * \brief 좌우로 이동하는 함수 (플레이어 캐릭터의 좌우 이동 함수를 불러온다)
	 * \param AxisValue 
	 */
	virtual void MoveRight(const float AxisValue);

	/**
	 * \brief 점프 시작
	 */
	virtual void JumpPressed();

	/**
	 * \brief 점프 끝 
	 */
	virtual void JumpReleased();

	/**
	 * \brief 달리기 시작
	 */
	virtual void RunPressed();

	/**
	 * \brief 달리기 끝
	 */
	virtual void RunReleased();

	/**
	 * \brief 앉기
	 */
	virtual void Crouch();

	/**
	 * \brief 엎드리기
	 */
	virtual void Prone();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	float ForwardBackAxis = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	float LeftRightAxis = 0.0f;
};
