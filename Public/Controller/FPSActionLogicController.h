// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/FPSWeaponLogicController.h"
#include "FPSActionLogicController.generated.h"

class AFPSActionLogicCharacter;
/**
 * 
 */
UCLASS()
class BATTLEROYAL_API AFPSActionLogicController : public AFPSWeaponLogicController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

protected:
	AFPSActionLogicCharacter* GetActionLogicCharacter() const;
	
	/**
	 * \brief 방어구 채우기
	 */
	virtual void ReplenishArmor();

	//------------- 택티컬 아이템 사용 ---------------------
	/**
	 * \brief 택티컬 아이템 사용 대기
	 */
	virtual void UseTacticalItemPressed();

	/**
	 * \brief 택티컬 아이템 사용
	 */
	virtual void UseTacticalItemReleased();
	//------------- 택티컬 아이템 사용 End -----------------
	 
	//------------- 살상 아이템 사용 -----------------------
	/**
	 * \brief 살상 아이템 사용 대기
	 */
	virtual void UseLethalItemPressed();

	/**
	 * \brief 살상 아이템 사용
	 */
	virtual void UseLethalItemReleased();
	//------------- 살상 아이템 사용 End -------------------
	
	/**
	 * \brief 상호작용
	 */
	virtual void Interaction();

	/**
	 * \brief 리스폰을 넣기 위해 JumpPressed(스페이스바)를 오버라이딩 함
	 */
	virtual void JumpPressed() override;

	/**
	 * \brief 무기 선택창 열기
	 */
public:
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	virtual void OpenOrCloseWeaponSelectUI();

protected:
	virtual void ClientOpenWeaponSelectUI();

public:
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	virtual void CloseWeaponSelectUI();

protected:
	//virtual void ClientCloseWeaponSelectUI();
	
	UFUNCTION(Server, Reliable)
	virtual void ServerRespawn();

	UFUNCTION(Client, Reliable)
	virtual void ClientRespawn();
};
