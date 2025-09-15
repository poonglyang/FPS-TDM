// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enum/GunEnum.h"
#include "PlayerMainUserWidget.generated.h"

/**
 * 
 */
class UTexture2D;

UCLASS()
class BATTLEROYAL_API UPlayerMainUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// ------------------------------ 무기 관련 ------------------------------------
	/**
	 * \brief 현재 들고 있는 무기의 아이콘을 설정하는 함수
	 * \param WeaponIcon 현재 들고 있는 무기의 아이콘
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon")
	void SetCurrentWeaponIcon(UTexture2D* WeaponIcon);
	virtual void SetCurrentWeaponIcon_Implementation(UTexture2D* WeaponIcon);

	/**
	 * \brief 현재 들고 있는 무기의 탄창에 장전된 탄약 개수를 UI에 띄우는 함수
	 * \param CurrentWeaponAmmoCount 현재 들고 있는 무기의 탄창에 장전된 탄약 개수
	 */	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon")
	void SetCurrentWeaponCurrentAmmo(int CurrentWeaponAmmoCount);
	virtual void SetCurrentWeaponCurrentAmmo_Implementation(int CurrentWeaponAmmoCount);

	/**
	 * \brief 현재 들고있는 무기 종류에 해당하는 예비 탄약을 UI에 띄우는 함수
	 * \param CurrentCharacterAmmoCount 현재 들고있는 무기 종류에 해당하는 예비 탄약 개수
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weapon")
	void SetCurrentCharacterAmmoCount(int CurrentCharacterAmmoCount);
	virtual void SetCurrentCharacterAmmoCount_Implementation(int CurrentCharacterAmmoCount);
	// ------------------------------ 무기 관련 End --------------------------------

	// ------------------------------ 수류탄 관련 ----------------------------------
	/**
	 * \brief UI에 장비한 살상 수류탄의 이미지를 설정하는 함수 
	 * \param LethalImage 살상 수류탄 이미지
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Projectile")
	void SetLethalImage(UTexture2D* LethalImage);
	void SetLethalImage_Implementation(UTexture2D* LethalImage);

	/**
	 * \brief UI에 장비한 살상 수류탄의 개수를 설정하는 함수
	 * \param LethalCount 살상 수류탄 개수
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Projectile")
	void SetLethalCount(int LethalCount);
	void SetLethalCount_Implementation(int LethalCount);

	/**
	 * \brief UI에 장비한 전술 수류탄의 이미지를 설정하는 함수 
	 * \param TacticalImage 전술 수류탄 이미지
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Projectile")
	void SetTacticalImage(UTexture2D* TacticalImage);
	void SetTacticalImage_Implementation(UTexture2D* TacticalImage);

	/**
	 * \brief UI에 장비한 전술 수류탄의 개수를 설정하는 함수
	 * \param TacticalCount 전술 수류탄 개수
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Projectile")
	void SetTacticalCount(int TacticalCount);
	void SetTacticalCount_Implementation(int TacticalCount);
	// ------------------------------ 수류탄 관련 End ------------------------------

	// ------------------------------ 자기 자신 방어구 관련 -------------------------
	/**
	 * \brief 자기 자신의 방어구 퍼센트 UI를 설정하는 함수
	 * \param OwnerPlayerArmorPercent 방어구 퍼센트
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "OwnerPlayer")
	void SetOwnerPlayerArmor(float OwnerPlayerArmorPercent);
	virtual void SetOwnerPlayerArmor_Implementation(float OwnerPlayerArmorPercent);


	/**
	 * \brief 자기 자신의 채력 퍼센트 UI를 설정하는 함수
	 * \param OwnerPlayerHealthPercent 채력 퍼센트
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "OwnerPlayer")
	void SetOwnerPlayerHealth(float OwnerPlayerHealthPercent);
	virtual void SetOwnerPlayerHealth_Implementation(float OwnerPlayerHealthPercent);

	/**
	 * \brief 자기자신의 파티 인덱스와 닉네임을 설정하는 함수
	 * \param OwnerPlayerIndex 자기 자신의 인덱스
	 * \param OwnerPlayerNickName 파티 닉네임
	 */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "OwnerPlayer")
	void SetOwnerPlayerIndexAndNickName(int32 OwnerPlayerIndex, const FString& OwnerPlayerNickName);
	void SetOwnerPlayerIndexAndNickName_Implementation(int32 OwnerPlayerIndex, const FString& OwnerPlayerNickName);
	// ------------------------------ 자기 자신 방어구 관련 End ---------------------

	// ------------------------------ 파티 플레이어 0 관련 --------------------------
	/**
	 * \brief 파티 플레이어 0의 채력과 방어력 UI를 설정하는 함수
	 * \param Player0Health 채력 퍼센트
	 * \param Player0Armor 방어력 퍼센트
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PartyPlayer0")
	void SetPartyPlayer0HealthAndArmor(float Player0Health, float Player0Armor);
	virtual void SetPartyPlayer0HealthAndArmor_Implementation(float Player0Health, float Player0Armor);

	/**
	 * \brief 파티 플레이어 0의 파티 번호와 닉네임 UI를 설정하는 함수
	 * \param Player0Index 플레이어 0의 파티 번수
	 * \param Player0NickName 플레이어 0의 닉네임 
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PartyPlayer0")
	void SetPartyPlayer0IndexAndNickname(int Player0Index, const FString& Player0NickName);
	virtual void SetPartyPlayer0IndexAndNickname_Implementation(int Player0Index, const FString& Player0NickName);

	/**
	 * \brief 플레이어 0이 없을 때 UI를 가리는 함수
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PartyPlayer0")
	void SetPartyPlayer0InfoHide();
	void SetPartyPlayer0InfoHide_Implementation();
	// ------------------------------ 파티 플레이어 0 관련 End ----------------------

	// ------------------------------ 파티 플레이어 1 관련 --------------------------
	/**
	 * \brief 파티 플레이어 1의 채력과 방어력 UI를 설정하는 함수
	 * \param Player1Health 채력 퍼센트
	 * \param Player1Armor 방어력 퍼센트
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PartyPlayer1")
	void SetPartyPlayer1HealthAndArmor(float Player1Health, float Player1Armor);
	virtual void SetPartyPlayer1HealthAndArmor_Implementation(float Player1Health, float Player1Armor);

	/**
	 * \brief 파티 플레이어 1의 파티 번호와 닉네임 UI를 설정하는 함수
	 * \param Player1Index 플레이어 1의 파티 번수
	 * \param Player1NickName 플레이어 1의 닉네임 
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PartyPlayer1")
	void SetPartyPlayer1IndexAndNickname(int Player1Index, const FString& Player1NickName);
	virtual void SetPartyPlayer1IndexAndNickname_Implementation(int Player1Index, const FString& Player1NickName);

	/**
	 * \brief 플레이어 1이 없을 때 UI를 가리는 함수
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PartyPlayer1")
	void SetPartyPlayer1InfoHide();
	void SetPartyPlayer1InfoHide_Implementation();
	// ------------------------------ 파티 플레이어 1 관련 End ----------------------

	// ------------------------------ 파티 플레이어 2 관련 --------------------------
	/**
	 * \brief 파티 플레이어 2의 채력과 방어력 UI를 설정하는 함수
	 * \param Player2Health 채력 퍼센트
	 * \param Player2Armor 방어력 퍼센트
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PartyPlayer2")
	void SetPartyPlayer2HealthAndArmor(float Player2Health, float Player2Armor);
	virtual void SetPartyPlayer2HealthAndArmor_Implementation(float Player2Health, float Player2Armor);

	/**
	 * \brief 파티 플레이어 2의 파티 번호와 닉네임 UI를 설정하는 함수
	 * \param Player2Index 플레이어 2의 파티 번수
	 * \param Player2NickName 플레이어 2의 닉네임 
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PartyPlayer2")
	void SetPartyPlayer2IndexAndNickname(int Player2Index, const FString& Player2NickName);
	virtual void SetPartyPlayer2IndexAndNickname_Implementation(int Player2Index, const FString& Player2NickName);

	/**
	 * \brief 플레이어 2가 없을 때 UI를 가리는 함수
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PartyPlayer2")
	void SetPartyPlayer2InfoHide();
	void SetPartyPlayer2InfoHide_Implementation();
	// ------------------------------ 파티 플레이어 2 관련 End ----------------------

	// ------------------------------ 파티 플레이어 3 관련 --------------------------
	/**
	 * \brief 파티 플레이어 3의 채력과 방어력 UI를 설정하는 함수
	 * \param Player3Health 채력 퍼센트
	 * \param Player3Armor 방어력 퍼센트
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PartyPlayer3")
	void SetPartyPlayer3HealthAndArmor(float Player3Health, float Player3Armor);
	virtual void SetPartyPlayer3HealthAndArmor_Implementation(float Player3Health, float Player3Armor);

	/**
	 * \brief 파티 플레이어 3의 파티 번호와 닉네임 UI를 설정하는 함수
	 * \param Player3Index 플레이어 3의 파티 번수
	 * \param Player3NickName 플레이어 3의 닉네임 
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PartyPlayer3")
	void SetPartyPlayer3IndexAndNickname(int Player3Index, const FString& Player3NickName);
	virtual void SetPartyPlayer3IndexAndNickname_Implementation(int Player3Index, const FString& Player3NickName);

	/**
	 * \brief 플레이어 3이 없을 때 UI를 가리는 함수
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PartyPlayer3")
	void SetPartyPlayer3InfoHide();
	void SetPartyPlayer3InfoHide_Implementation();
	// ------------------------------ 파티 플레이어 3 관련 End ----------------------

	// ------------------------------ 파티 플레이어 4 관련 --------------------------
	/**
	 * \brief 파티 플레이어 4의 채력과 방어력 UI를 설정하는 함수
	 * \param Player4Health 채력 퍼센트
	 * \param Player4Armor 방어력 퍼센트
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PartyPlayer4")
	void SetPartyPlayer4HealthAndArmor(float Player4Health, float Player4Armor);
	virtual void SetPartyPlayer4HealthAndArmor_Implementation(float Player4Health, float Player4Armor);

	/**
	 * \brief 파티 플레이어 4의 파티 번호와 닉네임 UI를 설정하는 함수
	 * \param Player4Index 플레이어 4의 파티 번수
	 * \param Player4NickName 플레이어 4의 닉네임 
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PartyPlayer4")
	void SetPartyPlayer4IndexAndNickname(int Player4Index, const FString& Player4NickName);
	virtual void SetPartyPlayer4IndexAndNickname_Implementation(int Player4Index, const FString& Player4NickName);

	/**
	 * \brief 플레이어 4이 없을 때 UI를 가리는 함수
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PartyPlayer4")
	void SetPartyPlayer4InfoHide();
	void SetPartyPlayer4InfoHide_Implementation();
	// ------------------------------ 파티 플레이어 4 관련 End ----------------------

	// ------------------------------ 파티 스코어 ----------------------------------
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PartyPlayer4")
	void SetPartyScore(int32 BlueTeamScore, int32 RedTeamScore, int32 TargetScore);
	// ------------------------------ 파티 스코어 End ------------------------------

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "WeaponShotType")
	void SetWeaponShotType(EShotType ShotTypeA, EShotType ShotTypeB);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "WeaponShotType")
	void SetShotTypeA();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "WeaponShotType")
	void SetShotTypeB();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponShotType")
	TMap<EShotType, UTexture2D*> ShotTypeMap;
};
