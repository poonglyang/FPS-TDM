// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/DamageFeedbadkHUD.h"
#include "TDMHUD.generated.h"

class UGameStartCoolDownUserWidget;
class UWaitGamePlayUserWidget;
class UPlayerDeathUserWidget;
/**
 * 
 */
class UKillLogUserWidget;
class UTDMEndUserWidget;
class UTexture2D;
UCLASS()
class BATTLEROYAL_API ATDMHUD : public ADamageFeedbadkHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UKillLogUserWidget* CreateKillLogWidget() const;

	UPlayerDeathUserWidget* CreatePlayerDeathWidget() const;

	UWaitGamePlayUserWidget* CreateWaitGamePlayUserWidget() const;

	UGameStartCoolDownUserWidget* CreateGameStartCoolDownWidget() const;

	UTDMEndUserWidget* CreateTDMEndUserWidget() const;
	
public:
	/**
	 * \brief 킬로그를 추가하는 함수
	 * \param KillPlayerName 죽인 플레이어 이름
	 * \param KillPlayerPartyNum 죽인 플레이어 파티 번호
	 * \param WeaponTexture 죽은 원인 이미지
	 * \param DeathPlayerPartyNum 죽은 플레이어 파티 번호
	 * \param DeathPlayerName 죽은 플레이어 이름
	 */
	UFUNCTION(BlueprintCallable, Category = "TDM HUD")
	virtual void AddKillLogWidget(const FString& KillPlayerName, int32 KillPlayerPartyNum, UTexture2D* WeaponTexture, int32 DeathPlayerPartyNum, const FString& DeathPlayerName);

	/**
	 * \brief 킬로그 지우기
	 */
	virtual void ClearKillLogWidget();

	/**
	 * \brief 죽었을 때 나오는 UI 띄우기
	 * \param KillPlayerName Owner를 죽인 플레이어 이름
	 */
	virtual void OwnerDeathUI(const FString& KillPlayerName);

	/**
	 * \brief 플레이어가 리스폰할 때 DeathUI을 없에기 위한 것
	 */
	virtual void OwnerRespawn();

	/**
	 * \brief 무기 선택창을 열거나 닫음
	 * \return 실행 성공시 true, 실패시 false 반환
	 */
	virtual bool OpenOrCloseWeaponSelectUI() override;
	

	virtual void SetGameModeAndMapName(const FText& NewGameModeName, const FText& NewMapName);

	virtual void SetPlayerCountInGameReadyWidget(int32 PlayerCount, int32 MinimumPlayers);

	virtual void RemoveGameReadyWidget();

	virtual void SetGamePlayCoolDown(int32 CoolTime);

	virtual void RemoveGamePlayCoolDownWidget();

	virtual void InitGameEndUserWidget(int32 RedTeamScore, int32 BlueTeamScore, bool bIsWin, UTexture2D* GameIcon);

	virtual void RemoveGameEndUserWidget();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDM HUD")
	TSubclassOf<UKillLogUserWidget> KillLogWidgetClass;
	
	UPROPERTY()
	UKillLogUserWidget* KillLogWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TDM HUD")
	FTimerHandle KillLogTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDM HUD")
	TSubclassOf<UPlayerDeathUserWidget> PlayerDeathWidgetClass;

	UPROPERTY()
	UPlayerDeathUserWidget* PlayerDeathWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDM HUD")
	TSubclassOf<UWaitGamePlayUserWidget> WaitGamePlayWidgetClass;

	UPROPERTY()
	UWaitGamePlayUserWidget* WaitGamePlayWidgetWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDM HUD")
	TSubclassOf<UGameStartCoolDownUserWidget> GameStartCoolDownWidgetClass;

	UPROPERTY()
	UGameStartCoolDownUserWidget* GameStartCoolDownWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TDM HUD")
	TSubclassOf<UTDMEndUserWidget> TDMEndUserWidgetClass;

	UPROPERTY()
	UTDMEndUserWidget* TDMEndUserWidget;
};
