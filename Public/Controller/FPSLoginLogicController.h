// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/FPSActionLogicController.h"
#include "Struct/PlayerStruct.h"
#include "FPSLoginLogicController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYAL_API AFPSLoginLogicController : public AFPSActionLogicController
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

	/**
	 * \brief 게임모드에게 클라이언트가 로그인 할 준비가 완료되었다고 알리는 함수
	 * \param NickName 불러온 닉네임
	 * \param LoginID 클라이언트의 로그인 아이디
	 */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "UserSession")
	virtual void ServerLoginReady(const FString& NickName, const FString& LoginID);

public:
	UFUNCTION()
	FPlayerAccountInfo GetPlayerAccountInfo();

	UFUNCTION()
	void SetPlayerAccountInfo(FPlayerAccountInfo NewPlayerAccountInfo);

	UFUNCTION()
	void SetPawnPartyIndex() const;
	
protected:
	UPROPERTY(BlueprintReadWrite, Replicated, EditAnywhere, Category = "PlayerLogin")
	FPlayerAccountInfo PlayerAccountInfo;
};
