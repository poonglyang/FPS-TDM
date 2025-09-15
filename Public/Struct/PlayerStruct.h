// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enum/PlayerEnum.h"
#include "Enum/GunEnum.h"
#include "Engine/DataTable.h"
#include "PlayerStruct.generated.h"

class AFPSActionLogicCharacter;
class AFPSUILogicController;
class AFPSUILogicCharacter;
class AFPSActionLogicController;
class UTexture2D;
/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(LOG_PlayerStruct, Log, All);

USTRUCT(Atomic, BlueprintType)
struct BATTLEROYAL_API FParty : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	FParty();

	void AddPlayer(FPlayerAccountInfo NewPlayer);

	void RemovePlayer(FPlayerAccountInfo NewPlayer);

	TArray<FPlayerAccountInfo> Party;
};


USTRUCT(Atomic, BlueprintType)
struct BATTLEROYAL_API FPlayerAccountInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FPlayerAccountInfo();
	
	FPlayerAccountInfo(
		AFPSActionLogicController* NewPlayerController,
		FGuid NewSetGuid = FGuid(),
		const FString& NewPlayerNickName = TEXT("UnknownPlayer"),
		int NewPartyIndex = -999,
		int NewPlayerIndex = -999,
		const FString& NewPlayerIPAddress = FString(TEXT("unknown")),
		const FString& NewPlayerLoginId = FString(TEXT("unknown"))
		);

	bool operator==(const FPlayerAccountInfo& Other) const;
	
	FGuid GetGuid() const;
	
	void SetGuid(FGuid NewSetGuid);

	AFPSActionLogicController* GetPlayerController();

	void SetPlayerController(AFPSActionLogicController* NewPlayerController);

	FString GetPlayerNickName() const;

	void SetPlayerNickName(const FString& NewPlayerNickName);

	int GetPartyIndex() const;

	void SetPartyIndex(int NewPartyIndex);

	int GetPlayerIndex() const;

	void SetPlayerIndex(int NewPlayerIndex);

	FString GetPlayerIPAddress() const;

	void SetPlayerIPAddress(const FString& NewPlayerIPAddress);

	FString GetPlayerLoginID() const;

	void SetPlayerLoginID(const FString& NewLoginID);

	float GetCurrentCharacterHealth() const;

	float GetCurrentCharacterMaxHealth() const;

	float GetCurrentCharacterArmor() const;

	float GetCurrentCharacterMaxArmor() const;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid PlayerGuid;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AFPSActionLogicController* FPSPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NickName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PartyIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PlayerIndexInParty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayerIPAddress;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayerLoginID;
};


USTRUCT(Atomic, BlueprintType)
struct BATTLEROYAL_API FCharacterState : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	FCharacterState()
	{
		MaxHp = 100;
		Hp = MaxHp;
		MaxArmor = 100;
		Armor = MaxArmor;
		MaxStamina = 100;
		Stamina = MaxStamina;
		bIsGameplay = true;
		OwnerCharacter = nullptr;
		NormalHealthRegenDelay = 5;
		NormalHealthRegenAmount = 1;
	}

	FCharacterState(
		AFPSActionLogicCharacter* NewOwnerCharacter,
		float MaxHp = 100,
		float Hp = 100,
		float MaxArmor = 100,
		float Armor = 100,
		float MaxStamina = 100,
		float Stamina = 100,
		bool bIsGameplay = true)
	: OwnerCharacter(NewOwnerCharacter), MaxHp(MaxHp), Hp(Hp), MaxArmor(MaxArmor), Armor(Armor), MaxStamina(MaxStamina), Stamina(Stamina), bIsGameplay(bIsGameplay)
	{
		NormalHealthRegenDelay = 5;
		NormalHealthRegenAmount = 1;
	};


	// ------------------------- Getter Setter -----------------------

	AFPSActionLogicCharacter* GetOwner() const;

	void SetOwnerCharacter(AFPSActionLogicCharacter* NewOwnerCharacter);
	
	float GetMaxHp() const;
	
	void SetMaxHp(float NewMaxHp);

	float GetHp() const;

	void SetHp(float NewHp);

	float GetMaxArmor() const;

	void SetMaxArmor(float NewMaxArmor);
	
	float GetArmor() const;

	void SetArmor(float NewArmor);

	float GetMaxStamina() const;

	void SetMaxStamina(float NewMaxStamina);
	
	float GetStamina() const;

	void SetStamina(float NewStamina);

	void SetIsGameplay(bool NewIsGameplay);

	float GetNormalHealthRegenDelay() const;

	void SetNormalHealthRegenDelay(float NewNormalHealthRegenDelay);

	float GetNormalHealthRegenAmount() const;

	void SetNormalHealthRegenAmount(float NewNormalHealthRegenAmount);
	
	// ------------------------- Getter Setter End -----------------------

	void GetDamage(float AmountDamage, FVector AttackLocation, AFPSUILogicController* AttackerController, UTexture2D* WeaponTexture ,bool bIsHeadShot = false);

	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AFPSActionLogicCharacter* OwnerCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxArmor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsGameplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NormalHealthRegenDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NormalHealthRegenAmount;
};

USTRUCT(Atomic, BlueprintType)
struct BATTLEROYAL_API FCarryAmmo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	FCarryAmmo()
	{
		MaxPistol = 30;
		Pistol = MaxPistol;
		MaxSMG = 120;
		SMG = MaxSMG;
		MaxAR = 150;
		AR = MaxAR;
		MaxLMG = 210;
		LMG = MaxLMG;
		MaxSniper = 20;
		Sniper = MaxSniper;
		MaxShotgun = 40;
		Shotgun = MaxShotgun;
		MaxRocket = 3;
		Rocket = MaxRocket;
		MaxTacticalProjectile = 1;
		TacticalProjectile = MaxTacticalProjectile;
		MaxLethalProjectile = 1;
		LethalProjectile = MaxLethalProjectile;
		OwnerCharacter = nullptr;
	}

	FCarryAmmo(
		int Pistol, int MaxPistol,
		int SMG, int MaxSMG,
		int AR, int MaxAR,
		int LMG, int MaxLMG,
		int Sniper, int MaxSniper,
		int Shotgun, int MaxShotgun,
		int Rocket, int MaxRocket,
		int TacticalProjectile, int MaxTacticalProjectile,
		int LethalProjectile, int MaxLethalProjectile)
	: Pistol(Pistol), MaxPistol(MaxPistol), SMG(SMG), MaxSMG(MaxSMG), AR(AR), MaxAR(MaxAR),LMG(LMG), MaxLMG(MaxLMG),
	Sniper(Sniper), MaxSniper(MaxSniper),Shotgun(Shotgun), MaxShotgun(MaxShotgun), Rocket(Rocket), MaxRocket(MaxRocket),
	TacticalProjectile(TacticalProjectile), MaxTacticalProjectile(MaxTacticalProjectile), LethalProjectile(LethalProjectile), MaxLethalProjectile(MaxLethalProjectile)
	{
		OwnerCharacter = nullptr;
	}

	int GetWeaponCarryAmmo(EWeaponType WeaponType) const
	{
		switch (WeaponType) {
		case EWeaponType::Pistol:
			return Pistol;
		case EWeaponType::AR:
			return AR;
		case EWeaponType::SMG:
			return SMG;
		case EWeaponType::LMG:
			return LMG;
		case EWeaponType::Shotgun:
			return Shotgun;
		case EWeaponType::Sniper:
			return Sniper;
		case EWeaponType::Rocket:
			return Rocket;
		}
		return 0;
	}

	void SetWeaponCarryAmmo(EWeaponType WeaponType, int NewAmmoCount);

	void AddWeaponCarryAmmo(EWeaponType WeaponType, int AddAmmoCount);

	void SetTacticalProjectile(int NewTacticalProjectile);

	void AddTacticalProjectile(int AddTacticalProjectile);

	int GetTacticalProjectile() const;

	void SetLethalProjectile(int NewLethalProjectile);

	void AddLethalProjectile(int AddLethalProjectile);

	int GetLethalProjectile();

	void SetOwner(AFPSUILogicCharacter* NewOwnerCharacter);

protected:
	void UpdateLethalCount() const;

	void UpdateTacticalCount() const;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AFPSUILogicCharacter* OwnerCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Pistol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxPistol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SMG;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxSMG;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAR;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LMG;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxLMG;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Sniper;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxSniper;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Shotgun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxShotgun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Rocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxRocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TacticalProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxTacticalProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LethalProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxLethalProjectile;
};

class BATTLEROYAL_API PlayerStruct
{
public:
	PlayerStruct();
	~PlayerStruct();
};
