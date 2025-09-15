// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Struct/PlayerStruct.h"
#include "PlayerLoginGameMode.generated.h"

class AFPSLoginLogicController;
/**
 * 
 */

DECLARE_LOG_CATEGORY_EXTERN(LOG_PlayerLoginGameMode, Log, All);

UCLASS()
class BATTLEROYAL_API APlayerLoginGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;

	/**
	 * \brief 플레이어의 IP Address를 반환하는 함수
	 * \param PlayerController 플레이어 컨트롤러
	 * \return 플레이어의 IP Address
	 */
	UFUNCTION(BlueprintPure, Category = "UserSession")
	FString GetClientIPAddress(APlayerController* PlayerController);

public:
	/**
	 * \brief 플레이어가 로그인 하는 함수, 클라이언트의 플레이어 컨트롤러에서 닉네임과 LoginID를 불러오는 것을 성공하면 로그인 준비가 되어 있다고 가정하고 이 함수를 실행 시킨다 
	 * \param LoginPlayerController 로그인한 플레이어 컨트롤러
	 * \param NickName 닉네임
	 * \param LoginID 로그인 ID
	 */
	virtual void PlayerLogin(AFPSLoginLogicController* LoginPlayerController, const FString& NickName, const FString& LoginID);

protected:
	/**
	 * \brief 플레이어가 다클라를 사용하는지 확인하는 함수
	 * \param LoginPlayerController 로그인한 플레이어 컨트롤러
	 * \param LoginID 로그인 ID
	 * \return 
	 */
	virtual bool CheckMultiClient(AFPSLoginLogicController* LoginPlayerController, const FString& LoginID);

	UFUNCTION(BlueprintCallable, Category = "UserSession")
	virtual void AddParty(AFPSLoginLogicController* LoginPlayerController, const FString& NickName,	const FString& LoginID);

	UFUNCTION(BlueprintCallable, Category = "UserSession")
	virtual bool SpawnPlayer(AFPSLoginLogicController* LoginPlayerController);

public:
	UFUNCTION(BlueprintCallable, Category = "UserSession")
	virtual FTransform GetPlayerRespawnTransform(AFPSActionLogicController* RespawnPlayerController);

	UFUNCTION(BlueprintCallable, Category = "UserSession")
	virtual void RespawnPlayer(AFPSActionLogicController* RespawnPlayerController);
	
protected:
	/**
	 * \brief 플레이어 스폰 지점
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerLogin")
	TArray<AActor*> PlayerStartPointArr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerLogin")
	int StartPointIndex = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerLogin")
	TArray<FPlayerAccountInfo> LoginPlayerInfoArr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerLogin")
	TArray<FParty> PartyArr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PlayerLogin")
	TSubclassOf<AFPSUILogicCharacter> PlayerPawnClass;
};
