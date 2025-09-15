// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/FPSLoginLogicController.h"
#include "FPSUILogicController.generated.h"

/**
 * 
 */
class UTexture2D;
class USoundBase;

UCLASS()
class BATTLEROYAL_API AFPSUILogicController : public AFPSLoginLogicController
{
	GENERATED_BODY()

public:
	/**
	 * \brief 자기 자신의 HP와 MP UI를 설정함
	 * \param HealthPercent Hp 퍼센트
	 * \param ArmorPercent Armor 퍼센트
	 */
	UFUNCTION(Client, Reliable)
	void SetOwnerHpAndArmorUI(float HealthPercent, float ArmorPercent) const;

	/**
	 * \brief 방어구에 피해를 입혔을 때 피드백을 주는 서버 함수
	 */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ServerAttackArmorFeedback();

protected:
	/**
	 * \brief 방어구에 피해를 입혔을 때 피드백을 주는 클라 함수
	 */
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientAttackArmorFeedback();

public:
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ServerAttackHpFeedback();

protected:
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientAttackHpFeedback();

public:
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ServerArmorBreakFeedback();

protected:
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientArmorBreakFeedback();

public:
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ServerKill(bool bIsHeadShot);

protected:
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientKill(bool bIsHeadShot);

public:
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientGetDamageFeedback(ACharacter* Attacker);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	virtual void ClientUpdateWeaponAmmoUI(float WeaponCurrentAmmo);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	virtual void ClientUpdateWeaponIconUI(UTexture2D* WeaponIcon);
	
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	virtual void ClientUpdateCharacterCarryAmmo(float CharacterCarryAmmo);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	virtual void SetOwnerPlayerIndexAndNickName(int Index, const FString& NickName);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void SetPartyPlayerArmorAndHealth(float HealthPercent, float ArmorPercent, int PartyIndex);
	
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void SetPartyValidPlayerIndexAndNickName(int PartyIndex, const FString& NickName);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void SetPartyNotValidPlayerHidden(int PartyIndex);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ServerInformPlayerGetDamage(float HealthPercent, float ArmorPercent);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ServerDead(AFPSUILogicController* Attacker, UTexture2D* WeaponTexture);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientAddKillLog(const FString& KillPlayerName, int32 KillPlayerPartyNum, UTexture2D* WeaponTexture, int32 DeathPlayerPartyNum, const FString& DeathPlayerName);

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ServerOwnerDeath(const FString& KillPlayerName);
	
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientOwnerDeath(const FString& KillPlayerName);
	
	virtual void ClientOpenWeaponSelectUI() override;

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	virtual void ClientCloseWeaponSelectUI();

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void SetLethalImage(UTexture2D* LethalImage);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void SetLethalCount(int LethalCount);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void SetTacticalImage(UTexture2D* TacticalImage);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void SetTacticalCount(int TacticalCount);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientSetPartyScore(int32 BlueTeamScore, int32 RedTeamScore, int32 TargetScore);
	
	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientSetGameModeAndMapName(const FText& NewGameModeName, const FText& NewMapName);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientSetPlayerCountInGameReadyWidget(int32 PlayerCount, int32 MinimumPlayers);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientRemoveGameReadyWidget();

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientSetGameStartCoolDown(int CoolTime);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientRemoveGameStartCoolDown();

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientGameEndUI(int32 RedTeamScore, int32 BlueTeamScore, bool bIsWin, UTexture2D* GameIcon);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientRemoveGameEndUI();

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void MoveToAnotherServer(FName LevelAddress);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientUpdateFriendIdentification();

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ServerUpdateFriendIdentification();

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientSetShotTypeIcon(EShotType ShotTypeA, EShotType ShotTypeB);

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientSetShotTypeA();

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientSetShotTypeB();

	UFUNCTION(Client, Reliable, BlueprintCallable, Category = "UILgoicController")
	void ClientFlashHitEffect(float Intensity, USoundBase* FlashSound);

	void FlashHitEffectEnd();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UILgoicController")
	USoundBase* ArmorHitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UILgoicController")
	USoundBase* ArmorBreakHitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UILgoicController")
	USoundBase* HpHitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UILgoicController")
	USoundBase* NormalKillSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UILgoicController")
	USoundBase* HeadShotKillSound;

	FTimerHandle FlashTimerHandle;
};
