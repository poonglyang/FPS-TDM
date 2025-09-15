// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/PlayerStruct.h"

#include "Character/FPSActionLogicCharacter.h"
#include "Character/FPSUILogicCharacter.h"
#include "Controller/FPSUILogicController.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY(LOG_PlayerStruct);

FParty::FParty()
{
}

void FParty::AddPlayer(FPlayerAccountInfo NewPlayer)
{
	Party.Add(NewPlayer);
}

void FParty::RemovePlayer(FPlayerAccountInfo NewPlayer)
{
	Party.Remove(NewPlayer);
}

FPlayerAccountInfo::FPlayerAccountInfo()
{
	PlayerGuid = FGuid();
	FPSPlayerController = nullptr;
	NickName = FString(TEXT("UnknownPlayer"));
	PartyIndex = -999;
	PlayerIndexInParty = -999;
	PlayerIPAddress = FString(TEXT("unknown"));
	PlayerLoginID = FString(TEXT("unknown"));
}

FPlayerAccountInfo::FPlayerAccountInfo(AFPSActionLogicController* NewPlayerController, FGuid NewSetGuid,
	const FString& NewPlayerNickName, int NewPartyIndex, int NewPlayerIndex, const FString& NewPlayerIPAddress,
	const FString& NewPlayerLoginId)
{
	PlayerGuid = NewSetGuid;
	FPSPlayerController = NewPlayerController;
	NickName = NewPlayerNickName;
	PartyIndex = NewPartyIndex;
	PlayerIndexInParty = NewPlayerIndex;
	PlayerIPAddress = NewPlayerIPAddress;
	PlayerLoginID = NewPlayerLoginId;
}

bool FPlayerAccountInfo::operator==(const FPlayerAccountInfo& Other) const
{
	return PlayerGuid == Other.PlayerGuid && FPSPlayerController == Other.FPSPlayerController && PlayerLoginID == Other.PlayerLoginID && PlayerIPAddress == Other.PlayerIPAddress && PlayerLoginID == Other.PlayerLoginID;
}

FGuid FPlayerAccountInfo::GetGuid() const
{
	return PlayerGuid;
}

void FPlayerAccountInfo::SetGuid(FGuid NewSetGuid)
{
	PlayerGuid = NewSetGuid;
}

AFPSActionLogicController* FPlayerAccountInfo::GetPlayerController()
{
	return FPSPlayerController;
}

void FPlayerAccountInfo::SetPlayerController(AFPSActionLogicController* NewPlayerController)
{
	FPSPlayerController = NewPlayerController;
}

FString FPlayerAccountInfo::GetPlayerNickName() const
{
	return NickName;
}

void FPlayerAccountInfo::SetPlayerNickName(const FString& NewPlayerNickName)
{
	NickName = NewPlayerNickName;
}

int FPlayerAccountInfo::GetPartyIndex() const
{
	return PartyIndex;
}

void FPlayerAccountInfo::SetPartyIndex(int NewPartyIndex)
{
	PartyIndex = NewPartyIndex;
}

int FPlayerAccountInfo::GetPlayerIndex() const
{
	return PlayerIndexInParty;
}

void FPlayerAccountInfo::SetPlayerIndex(int NewPlayerIndex)
{
	PlayerIndexInParty = NewPlayerIndex;
}

FString FPlayerAccountInfo::GetPlayerIPAddress() const
{
	return PlayerIPAddress;
}

void FPlayerAccountInfo::SetPlayerIPAddress(const FString& NewPlayerIPAddress)
{
	PlayerIPAddress = NewPlayerIPAddress;
}

FString FPlayerAccountInfo::GetPlayerLoginID() const
{
	return PlayerLoginID;
}

void FPlayerAccountInfo::SetPlayerLoginID(const FString& NewLoginID)
{
	PlayerLoginID = NewLoginID;
}

float FPlayerAccountInfo::GetCurrentCharacterHealth() const
{
	if (AFPSBaseCharacter* CurrentCharacter = Cast<AFPSBaseCharacter>(FPSPlayerController->GetPawn()))
	{
		return  CurrentCharacter->CharacterState.GetHp();
	}

	return 0;
}

float FPlayerAccountInfo::GetCurrentCharacterMaxHealth() const
{
	if (AFPSBaseCharacter* CurrentCharacter = Cast<AFPSBaseCharacter>(FPSPlayerController->GetPawn()))
	{
		return  CurrentCharacter->CharacterState.GetMaxHp();
	}

	return 0;
}

float FPlayerAccountInfo::GetCurrentCharacterMaxArmor() const
{
	if (AFPSBaseCharacter* CurrentCharacter = Cast<AFPSBaseCharacter>(FPSPlayerController->GetPawn()))
	{
		return  CurrentCharacter->CharacterState.GetMaxArmor();
	}

	return 0;
}

float FPlayerAccountInfo::GetCurrentCharacterArmor() const
{
	if (AFPSBaseCharacter* CurrentCharacter = Cast<AFPSBaseCharacter>(FPSPlayerController->GetPawn()))
	{
		return  CurrentCharacter->CharacterState.GetArmor();
	}

	return 0;
}

AFPSActionLogicCharacter* FCharacterState::GetOwner() const
{
	return OwnerCharacter;
}

void FCharacterState::SetOwnerCharacter(AFPSActionLogicCharacter* NewOwnerCharacter)
{
	OwnerCharacter = NewOwnerCharacter;
}

float FCharacterState::GetMaxHp() const
{
	return MaxHp;
}

void FCharacterState::SetMaxHp(float NewMaxHp)
{
	MaxHp = NewMaxHp;
}

float FCharacterState::GetHp() const
{
	return Hp;
}

void FCharacterState::SetHp(float NewHp)
{
	//UE_LOG(LOG_PlayerStruct, Log, TEXT("%d"), bIsGameplay);
	Hp = FMath::Clamp(NewHp, bIsGameplay ? 0.f : 1.f, MaxHp);

	if (OwnerCharacter)
		return;
	
	if (AFPSUILogicController* CurrentOwnerController = Cast<AFPSUILogicController>(OwnerCharacter->GetController()))
	{
		CurrentOwnerController->SetOwnerHpAndArmorUI(Hp/MaxHp, Armor/MaxArmor);
		CurrentOwnerController->ServerInformPlayerGetDamage(Hp/MaxHp, Armor/MaxArmor);
	}
}

float FCharacterState::GetMaxArmor() const
{
	return MaxArmor;
}

void FCharacterState::SetMaxArmor(float NewMaxArmor)
{
	MaxArmor = NewMaxArmor;
}

float FCharacterState::GetArmor() const
{
	return Armor;
}

void FCharacterState::SetArmor(float NewArmor)
{
	Armor = FMath::Clamp(NewArmor, 0.f, MaxArmor);

	if (!OwnerCharacter)
		return;
	
	if (AFPSUILogicController* CurrentOwnerController = Cast<AFPSUILogicController>(OwnerCharacter->GetController()))
	{
		CurrentOwnerController->SetOwnerHpAndArmorUI(Hp/MaxHp, Armor/MaxArmor);
		CurrentOwnerController->ServerInformPlayerGetDamage(Hp/MaxHp, Armor/MaxArmor);
	}
}

float FCharacterState::GetMaxStamina() const
{
	return MaxStamina;
}

void FCharacterState::SetMaxStamina(float NewMaxStamina)
{
	MaxStamina = NewMaxStamina;
}

float FCharacterState::GetStamina() const
{
	return Stamina;
}

void FCharacterState::SetStamina(float NewStamina)
{
	Stamina =  FMath::Clamp(NewStamina, 0.f, MaxStamina);;
}

void FCharacterState::SetIsGameplay(bool NewIsGameplay)
{
	bIsGameplay = NewIsGameplay;
}

float FCharacterState::GetNormalHealthRegenDelay() const
{
	return NormalHealthRegenDelay;
}

void FCharacterState::SetNormalHealthRegenDelay(float NewNormalHealthRegenDelay)
{
	NormalHealthRegenDelay = NewNormalHealthRegenDelay;
}

float FCharacterState::GetNormalHealthRegenAmount() const
{
	return NormalHealthRegenAmount;
}

void FCharacterState::SetNormalHealthRegenAmount(float NewNormalHealthRegenAmount)
{
	NormalHealthRegenAmount = NewNormalHealthRegenAmount;
}

void FCharacterState::GetDamage(float AmountDamage, FVector AttackLocation, AFPSUILogicController* AttackerController, UTexture2D* WeaponTexture ,bool bIsHeadShot)
{
	if (!OwnerCharacter)
		return;

	if (!AttackerController)
		return;
	
	AFPSUILogicController* CurrentOwnerController = Cast<AFPSUILogicController>(OwnerCharacter->GetController());

	if (!CurrentOwnerController)
		return;
	
	if (Armor > 0)
	{
		float RemainingDamage = AmountDamage - Armor;
		
		SetArmor(Armor - AmountDamage);
		
		if (RemainingDamage > 0)
		{
			SetHp(Hp - RemainingDamage);
			
		}

		if (Armor <= 0)
		{
			AttackerController->ServerArmorBreakFeedback();	// 방어구가 깨지면 방어구 깨짐 효과 
		}
		else
		{
			AttackerController->ServerAttackArmorFeedback(); // 방어구가 깨지지 않았으면 방어구 타격 효과
		}
	}
	else
	{
		SetHp(Hp - AmountDamage);
		if (Hp > 0)
		{
			AttackerController->ServerAttackHpFeedback();	// 채력 타격 효과
			OwnerCharacter->ServerStartHealthRegen(NormalHealthRegenDelay, NormalHealthRegenAmount);
		}
		else
		{
			AttackerController->ServerKill(bIsHeadShot);
			CurrentOwnerController->ServerDead(AttackerController, WeaponTexture);
		}
		
	}

	if (Cast<ACharacter>(AttackerController->GetPawn()))
	{
		CurrentOwnerController->ClientGetDamageFeedback(Cast<ACharacter>(AttackerController->GetPawn()));	// 피격 효과
		CurrentOwnerController->SetOwnerHpAndArmorUI(Hp/MaxHp, Armor/MaxArmor);
		CurrentOwnerController->ServerInformPlayerGetDamage(Hp/MaxHp, Armor/MaxArmor);
	}
	
	UE_LOG(LOG_PlayerStruct, Log, TEXT("Hp : %f, Armor : %f"), Hp, Armor);
}

void FCarryAmmo::SetWeaponCarryAmmo(EWeaponType WeaponType, int NewAmmoCount)
{
	switch (WeaponType) {
	case EWeaponType::Pistol:
		Pistol = NewAmmoCount;
		break;
	case EWeaponType::AR:
		AR = NewAmmoCount;
		break;
	case EWeaponType::SMG:
		SMG = NewAmmoCount;
		break;
	case EWeaponType::LMG:
		LMG = NewAmmoCount;
		break;
	case EWeaponType::Shotgun:
		Shotgun = NewAmmoCount;
		break;
	case EWeaponType::Sniper:
		Sniper = NewAmmoCount;
		break;
	case EWeaponType::Rocket:
		Rocket = NewAmmoCount;
		break;
	}

	if (!OwnerCharacter)
		return;

	AFPSUILogicController* CurrentController = Cast<AFPSUILogicController>(OwnerCharacter->GetController());
	
	if (CurrentController)
		CurrentController->ClientUpdateCharacterCarryAmmo(NewAmmoCount);
	
		
	
}

void FCarryAmmo::AddWeaponCarryAmmo(EWeaponType WeaponType, int AddAmmoCount)
{
	int CurrentAmmo = 0;
	
	switch (WeaponType) {
	case EWeaponType::Pistol:
		Pistol = FMath::Clamp(Pistol + AddAmmoCount, 0 , MaxPistol);
		CurrentAmmo = Pistol;
		break;
	case EWeaponType::AR:
		AR = FMath::Clamp(AR + AddAmmoCount, 0 , MaxAR);
		CurrentAmmo = AR;
		break;
	case EWeaponType::SMG:
		SMG = FMath::Clamp(SMG + AddAmmoCount, 0 , MaxSMG);
		CurrentAmmo = SMG;
		break;
	case EWeaponType::LMG:
		LMG = FMath::Clamp(LMG + AddAmmoCount, 0 , MaxLMG);
		CurrentAmmo = LMG;
		break;
	case EWeaponType::Shotgun:
		Shotgun = FMath::Clamp(Shotgun + AddAmmoCount, 0 , MaxShotgun);
		CurrentAmmo = Shotgun;
		break;
	case EWeaponType::Sniper:
		Sniper = FMath::Clamp(Sniper + AddAmmoCount, 0 , MaxSniper);
		CurrentAmmo = Sniper;
		break;
	case EWeaponType::Rocket:
		Rocket = FMath::Clamp(Rocket + AddAmmoCount, 0 , MaxRocket);
		CurrentAmmo = Rocket;
		break;
	}

	AFPSUILogicController* CurrentController = Cast<AFPSUILogicController>(OwnerCharacter->GetController());
	
	if (CurrentController)
		CurrentController->ClientUpdateCharacterCarryAmmo(CurrentAmmo);
}

void FCarryAmmo::SetTacticalProjectile(int NewTacticalProjectile)
{
	TacticalProjectile = NewTacticalProjectile;
	UpdateTacticalCount();
}

void FCarryAmmo::AddTacticalProjectile(int AddTacticalProjectile)
{
	TacticalProjectile = FMath::Clamp(TacticalProjectile + AddTacticalProjectile, 0, MaxTacticalProjectile);
	UpdateTacticalCount();
}

int FCarryAmmo::GetTacticalProjectile() const
{
	return TacticalProjectile;
}

void FCarryAmmo::SetLethalProjectile(int NewLethalProjectile)
{
	LethalProjectile = NewLethalProjectile;
	UpdateLethalCount();
}

void FCarryAmmo::AddLethalProjectile(int AddLethalProjectile)
{
	LethalProjectile = FMath::Clamp(LethalProjectile + AddLethalProjectile, 0, MaxLethalProjectile);
	UpdateLethalCount();
}

int FCarryAmmo::GetLethalProjectile()
{
	return LethalProjectile;
}

void FCarryAmmo::SetOwner(AFPSUILogicCharacter* NewOwnerCharacter)
{
	OwnerCharacter = NewOwnerCharacter;
}

void FCarryAmmo::UpdateLethalCount() const
{
	if (AFPSUILogicController* CurrentOwnerController = Cast<AFPSUILogicController>(OwnerCharacter->GetController()))
	{
		CurrentOwnerController->SetLethalCount(LethalProjectile);
		
	}
	
}

void FCarryAmmo::UpdateTacticalCount() const
{
	if (AFPSUILogicController* CurrentOwnerController = Cast<AFPSUILogicController>(OwnerCharacter->GetController()))
	{
		CurrentOwnerController->SetTacticalCount(TacticalProjectile);
	}
}


PlayerStruct::PlayerStruct()
{
}

PlayerStruct::~PlayerStruct()
{
}
