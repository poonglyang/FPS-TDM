// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enum/GunEnum.h"
#include "HUD/BaseHUD.h"
#include "PlayerMainHUD.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LOG_PlayerMainHUD, Log, All);

class UPlayerMainUserWidget;
class UTexture2D;
class UWeaponSelectUserWidget;
/**
 * 
 */
UCLASS()
class BATTLEROYAL_API APlayerMainHUD : public ABaseHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	/**
	 * \brief PlayerMain위젯을 만들고 Viewport에 넣는 함수
	 */
	void CreatePlayerMainUserWidget();

	void CreateWeaponSelectUserWidget();

public:
	/**
	 * \brief 플레이어(자기자신)의 방어구와 채력 UI 설정
	 * \param ArmorPercent 방탄복 퍼센트
	 * \param HealthPercent 채력 퍼센트
	 */
	UFUNCTION(BlueprintCallable, Category = "PlayerMainHUD OwnerPlayerState")
	void SetOwnerPlayerArmorAndHealth(float ArmorPercent, float HealthPercent);

	UFUNCTION(BlueprintCallable, Category = "PlayerMainHUD OwnerPlayerState")
	void SetOwnerPlayerIndexAndNickName(int Index, const FString& NickName);
	
	/**
	 * \brief 현재 들고 있는 무기의 탄창에 장전된 탄약 개수를 UI에 띄우는 함수
	 * \param CurrentWeaponAmmoCount 현재 들고 있는 무기의 탄창에 장전된 탄약 개수
	 */
	UFUNCTION(BlueprintCallable, Category = "PlayerMainHUD Weapon")
	void SetCurrentWeaponCurrentAmmo(int CurrentWeaponAmmoCount);

	/**
	 * \brief 현재 들고있는 무기 종류에 해당하는 예비 탄약을 UI에 띄우는 함수
	 * \param CurrentCharacterAmmoCount 현재 들고있는 무기 종류에 해당하는 예비 탄약 개수
	 */
	UFUNCTION(BlueprintCallable, Category = "PlayerMainHUD Weapon")
	void SetCurrentCharacterAmmoCount(int CurrentCharacterAmmoCount);

	/**
	 * \brief 현재 들고 있는 무기의 아이콘을 설정하는 함수
	 * \param WeaponIcon 현재 들고 있는 무기의 아이콘
	 */
	UFUNCTION(BlueprintCallable, Category = "PlayerMainHUD Weapon")
	void SetCurrentWeaponIcon(UTexture2D* WeaponIcon);

	/**
	 * \brief UI에 장비한 살상 수류탄의 이미지를 설정하는 함수 
	 * \param LethalImage 살상 수류탄 이미지
	 */
	UFUNCTION(BlueprintCallable, Category = "PlayerMainHUD Weapon")
	void SetLethalImage(UTexture2D* LethalImage);

	/**
	 * \brief UI에 장비한 살상 수류탄의 개수를 설정하는 함수
	 * \param LethalCount 살상 수류탄 개수
	 */
	UFUNCTION(BlueprintCallable, Category = "PlayerMainHUD Weapon")
	void SetLethalCount(int LethalCount);

	/**
	 * \brief UI에 장비한 전술 수류탄의 이미지를 설정하는 함수 
	 * \param TacticalImage 전술 수류탄 이미지
	 */
	UFUNCTION(BlueprintCallable, Category = "PlayerMainHUD Weapon")
	void SetTacticalImage(UTexture2D* TacticalImage);

	/**
	 * \brief UI에 장비한 전술 수류탄의 개수를 설정하는 함수
	 * \param TacticalCount 전술 수류탄 개수
	 */
	UFUNCTION(BlueprintCallable, Category = "PlayerMainHUD Weapon")
	void SetTacticalCount(int TacticalCount);

	/**
	 * \brief OldPartyIndex가 사용 자기 자신이거나 플레이어 컨트롤러가 없으면 false를 있으면 갱신해야 하는 파티원 Index를 계산한다
	 * \param OldPartyIndex 계산전 파티 인덱스
	 * \param NewPartyIndex 계산 후 파티 인덱스
	 * \return 파티원 상태 UI를 갱신해도 되는지 여부
	 */
	bool CalcPartyIndex(int OldPartyIndex, int& NewPartyIndex) const;
	
	/**
	 * \brief PartyIndex에 해당하는 파티원의 상태를 변경하는 UI
	 * \param HealthPercent 채력 퍼센트
	 * \param ArmorPercent 방어력 퍼센트
	 * \param PartyIndex 변경할 파티원 인덱스
	 */
	UFUNCTION(BlueprintCallable, Category = "PlayerMainHUD PartyState")
	void SetPartyPlayerArmorAndHealth(float HealthPercent, float ArmorPercent, int PartyIndex);
	
	UFUNCTION(BlueprintCallable, Category = "PlayerMainHUD PartyState")
	void SetPartyValidPlayerIndexAndNickName(int PartyIndex, const FString& NickName);

	UFUNCTION(BlueprintCallable, Category = "PlayerMainHUD PartyState")
	void SetPartyNotValidPlayerHidden(int PartyIndex);

	UFUNCTION(BlueprintCallable, Category = "Weapon Select")
	virtual bool OpenOrCloseWeaponSelectUI();

	UFUNCTION(BlueprintCallable, Category = "Weapon Select")
	virtual void CloseWeaponSelectUI();
	
	UFUNCTION(BlueprintCallable, Category = "Party Score")
	void SetPartyScore(int32 BlueTeamScore, int32 RedTeamScore, int32 TargetScore);

	UFUNCTION(BlueprintCallable, Category = "Weapon ShotType")
	void SetShotTypeIcon(EShotType ShotTypeA, EShotType ShotTypeB);

	UFUNCTION(BlueprintCallable, Category = "Weapon ShotType")
	void SetShotTypeA();
	
	UFUNCTION(BlueprintCallable, Category = "Weapon ShotType")
	void SetShotTypeB();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMainHUD")
	TSubclassOf<UPlayerMainUserWidget> PlayerMainUserWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerMainHUD")
	UPlayerMainUserWidget* PlayerMainUserWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Select")
	TSubclassOf<UWeaponSelectUserWidget> WeaponSelectUserWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Select")
	UWeaponSelectUserWidget* WeaponSelectUserWidget;

};
