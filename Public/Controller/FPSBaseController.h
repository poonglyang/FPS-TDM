// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSBaseController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYAL_API AFPSBaseController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	/**
	 * \brief 입력을 할 수 있는지에 대한 bool값 
	 */
	UPROPERTY(BlueprintReadWrite, Replicated, EditAnywhere, Category = "Input")
	bool bIsCanWork = true;

	/**
	 * \brief 플레이어가 살아 있는지에 대한 bool 값
	 */
	UPROPERTY(BlueprintReadWrite, Replicated, EditAnywhere, Category = "Input")
	bool bIsPlayerAlive = true;
};
