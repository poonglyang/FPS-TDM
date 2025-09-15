// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/FPSActionLogicCharacter.h"
#include "FPSUILogicCharacter.generated.h"

/**
 * 
 */
class UWidgetComponent;

UCLASS()
class BATTLEROYAL_API AFPSUILogicCharacter : public AFPSActionLogicCharacter
{
	GENERATED_BODY()

public:
	AFPSUILogicCharacter();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="UILogicCharacter")
	UWidgetComponent* DiscriminationWidget;

	
	
public:
	UFUNCTION()
	virtual void OnRep_TeamNum();
	
	void SetCharacterTeamNum(int32 NewTeamNum);

	int GetCharacterTeamNum() const;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="UILogicCharacter")
	void ActiveFriendlyIdentification();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_TeamNum)
	int32 TeamNum;
};
