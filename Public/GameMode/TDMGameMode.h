// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/PlayerLoginGameMode.h"
#include "TDMGameMode.generated.h"

class ABaseWeapon;
/**
 * 
 */
class AFPSUILogicController;
class UTexture2D;

DECLARE_LOG_CATEGORY_EXTERN(LOG_TDMGameMode, Log, All);

UENUM(BlueprintType)
enum class EGameState : uint8
{
	/**
	 * \brief Game Ready
	 * 게임을 준비하는 단계\n
	 * 플레이어가 들어오면 대기 창을 띄움\n
	 * 플레이어가 움직일 수 없음\n
	 */
	GameReady UMETA(DisplayName = "Game Ready"),

	/**
	 * \brief Game Start
	 * 게임 시작을 하는 단계\n
	 * 플레이어 대기창 제거\n
	 * 플레이어 무기 선택창 오픈\n
	 * 플레이어는 움직일 수 없음\n
	 */
	GameStart UMETA(DisplayName = "Game Start"),

	/**
	 * \brief Game In Progress
	 * 게임 중\n
	 * 플레이어는 움직이며 이것저것 다 할 수 있음
	 */
	GameInProgress UMETA(DisplayName = "Game In Progress"),
	
	/**
	 * \brief Game End
	 * 게임 종료\n
	 * 제한 시간 또는 일정 킬수를 만족해 게임이 종료됨\n
	 * 플레이어는 움직일 수 없음\n
	 * 결과창 출력\n
	 * 출력뒤 카운트 다운이 생성되고 카운트 다운 뒤 플레이어는 강제로 로비로 이동함\n
	 */
	GameEnd UMETA(DisplayName = "Game End"),
};


UCLASS()
class BATTLEROYAL_API ATDMGameMode : public APlayerLoginGameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void AddParty(AFPSLoginLogicController* LoginPlayerController, const FString& NickName, const FString& LoginID) override;

	virtual void PlayerLogin(AFPSLoginLogicController* LoginPlayerController, const FString& NickName, const FString& LoginID) override;

	virtual void RespawnPlayer(AFPSActionLogicController* RespawnPlayerController) override;

public:
	virtual void UpdateRedTeamPartyInfo();

	virtual void UpdateBlueTeamPartyInfo();

	virtual void PlayerDead(AFPSUILogicController* DeadPlayerController, AFPSUILogicController* AttackPlayerController, UTexture2D* WeaponTexture);

	void GameStart();

	void GameStartCoolDown();

	void GameInProgress();

	void GameEnd();

	void BackToLobby();
	
	void InitServer();

	void UpdateTeamDiscrimination();

	void UpdateRedTeamDiscrimination();

	void UpdateBlueTeamDiscrimination();
protected:
	UPROPERTY()
	EGameState CurrentGameState = EGameState::GameReady;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDM GameMode");
	int32 MinimumPlayers = 2;
	
	UPROPERTY()
	TArray<AActor*> RandomSpawn;
	
	UPROPERTY()
	TArray<AActor*> RedTeamStartSpawn;

	int32 RedTeamStartPointIndex = 0;
	
	UPROPERTY()
	TArray<AActor*> BlueTeamStartSpawn;

	int32 BlueTeamStartPointIndex = 0;
	
	UPROPERTY()
	TArray<FPlayerAccountInfo> RedTeam;

	UPROPERTY()
	TArray<FPlayerAccountInfo> BlueTeam;

	UPROPERTY()
	int32 KillLogSelf = 0;

	UPROPERTY()
	int32 RedTeamScore = 0;
	
	UPROPERTY()
	int32 BlueTeamScore = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDM Game Mode")
	int32 TargetScore = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDM GameMode");
	TSubclassOf<ABaseWeapon> DefaultWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDM GameMode");
	FText GameModeName = FText::GetEmpty();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDM GameMode");
	FText GameMapName = FText::GetEmpty();

	UPROPERTY()
	FTimerHandle RemoveWaitUIHandle;
	
	UPROPERTY()
	FTimerHandle GameStarTTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDM GameMode")
	int32 DefaultGameStartCoolTime = 15;
	
	int32 GameStartCoolTime = 15;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDM GameMode")
	UTexture2D* GameIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDM GameMode")
	float InitDelay = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDM GameMode")
	FName LobbyServerAddress;
};
