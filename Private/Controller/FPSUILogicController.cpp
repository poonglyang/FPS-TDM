// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/FPSUILogicController.h"

#include "Character/FPSUILogicCharacter.h"
#include "GameFramework/Character.h"
#include "GameMode/TDMGameMode.h"
#include "HUD/DamageFeedbadkHUD.h"
#include "HUD/TDMHUD.h"
#include "Kismet/GameplayStatics.h"

void AFPSUILogicController::ServerAttackArmorFeedback_Implementation()
{
	ClientAttackArmorFeedback();
}

void AFPSUILogicController::ClientAttackArmorFeedback_Implementation()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ArmorHitSound, 0.4f);
	
	if (ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD()))
	{
		CurrentHUD->SetHitArmor(false);
		CurrentHUD->SetHitEffect(false);
	}
}

void AFPSUILogicController::ServerArmorBreakFeedback_Implementation()
{
	ClientArmorBreakFeedback();
}

void AFPSUILogicController::ClientArmorBreakFeedback_Implementation()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ArmorBreakHitSound, 0.5f);
	
	if (ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD()))
	{
		CurrentHUD->SetHitArmor(true);
		CurrentHUD->SetHitEffect(false);
	}
}


void AFPSUILogicController::ServerAttackHpFeedback_Implementation()
{
	ClientAttackHpFeedback();
}

void AFPSUILogicController::ClientAttackHpFeedback_Implementation()
{
	UGameplayStatics::PlaySound2D(GetWorld(), HpHitSound, 0.4f);
	
	if (ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD()))
	{
		CurrentHUD->SetHitEffect(false);
	}
}

void AFPSUILogicController::ServerKill_Implementation(bool bIsHeadShot)
{
	ClientKill(bIsHeadShot);
}

void AFPSUILogicController::ClientKill_Implementation(bool bIsHeadShot)
{
	if (bIsHeadShot)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), HeadShotKillSound, 0.5f);
	}
	else
	{
		UGameplayStatics::PlaySound2D(GetWorld(), NormalKillSound, 0.5f);
	}

	if (ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD()))
	{
		CurrentHUD->SetHitEffect(false);
	}
}

void AFPSUILogicController::ClientGetDamageFeedback_Implementation(ACharacter* Attacker)
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());

	ACharacter* CurrentCharacter = Cast<ACharacter>(GetPawn());
	
	if (!CurrentHUD || !CurrentCharacter) return;
	
	CurrentHUD->SetDynamicDamageFeedback(Attacker, CurrentCharacter);
}

void AFPSUILogicController::ClientUpdateWeaponIconUI_Implementation(UTexture2D* WeaponIcon)
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->SetCurrentWeaponIcon(WeaponIcon);
}


void AFPSUILogicController::ClientUpdateWeaponAmmoUI_Implementation(float WeaponCurrentAmmo)
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->SetCurrentWeaponCurrentAmmo(WeaponCurrentAmmo);
}

void AFPSUILogicController::ClientUpdateCharacterCarryAmmo_Implementation(float CharacterCarryAmmo)
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->SetCurrentCharacterAmmoCount(CharacterCarryAmmo);
}

void AFPSUILogicController::SetOwnerHpAndArmorUI_Implementation(float HealthPercent, float ArmorPercent) const
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->SetOwnerPlayerArmorAndHealth(ArmorPercent, HealthPercent);
}

void AFPSUILogicController::SetOwnerPlayerIndexAndNickName_Implementation(int Index, const FString& NickName)
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->SetOwnerPlayerIndexAndNickName(Index, NickName);
}

void AFPSUILogicController::SetPartyPlayerArmorAndHealth_Implementation(float HealthPercent, float ArmorPercent,
	int PartyIndex)
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->SetPartyPlayerArmorAndHealth(HealthPercent, ArmorPercent, PartyIndex);
}

void AFPSUILogicController::SetPartyValidPlayerIndexAndNickName_Implementation(int PartyIndex, const FString& NickName)
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->SetPartyValidPlayerIndexAndNickName(PartyIndex, NickName);
}

void AFPSUILogicController::SetPartyNotValidPlayerHidden_Implementation(int PartyIndex)
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->SetPartyNotValidPlayerHidden(PartyIndex);
}

void AFPSUILogicController::ServerInformPlayerGetDamage_Implementation(float HealthPercent, float ArmorPercent)
{
	ATDMGameMode* CurrentGameMode = Cast<ATDMGameMode>( UGameplayStatics::GetGameMode(GetWorld()));
	if (!CurrentGameMode)
		return;

	PlayerAccountInfo.GetPartyIndex() == 1 ? CurrentGameMode->UpdateRedTeamPartyInfo() : CurrentGameMode->UpdateBlueTeamPartyInfo();
}

void AFPSUILogicController::ServerDead_Implementation(AFPSUILogicController* Attacker, UTexture2D* WeaponTexture)
{
	ATDMGameMode* CurrentGameMode = Cast<ATDMGameMode>( UGameplayStatics::GetGameMode(GetWorld()));
	if (!CurrentGameMode)
		return;

	CurrentGameMode->PlayerDead(this, Attacker, WeaponTexture);
}


void AFPSUILogicController::ClientAddKillLog_Implementation(const FString& KillPlayerName, int32 KillPlayerPartyNum,
	UTexture2D* WeaponTexture, int32 DeathPlayerPartyNum, const FString& DeathPlayerName)
{
	ATDMHUD* CurrentHUD = Cast<ATDMHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->AddKillLogWidget(KillPlayerName, KillPlayerPartyNum, WeaponTexture, DeathPlayerPartyNum, DeathPlayerName);
}

void AFPSUILogicController::ServerOwnerDeath_Implementation(const FString& KillPlayerName)
{
	ClientOwnerDeath(KillPlayerName);
	UnPossess();
	bIsPlayerAlive = false;
}

void AFPSUILogicController::ClientOwnerDeath_Implementation(const FString& KillPlayerName)
{
	ATDMHUD* CurrentHUD = Cast<ATDMHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->OwnerDeathUI(KillPlayerName);
}


void AFPSUILogicController::ClientOpenWeaponSelectUI()
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());
	if (!CurrentHUD)
	{
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("왜 캐스트가 안되는건데, %s"), *GetHUD()->GetName()));
		return;
	}
		
	
	if (CurrentHUD->OpenOrCloseWeaponSelectUI())
	{

	}
}



void AFPSUILogicController::ClientSetShotTypeIcon_Implementation(EShotType ShotTypeA, EShotType ShotTypeB)
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());
	if (!CurrentHUD)
	{
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("왜 캐스트가 안되는건데, %s"), *GetHUD()->GetName()));
		return;
	}

	CurrentHUD->SetShotTypeIcon(ShotTypeA, ShotTypeB);
}

void AFPSUILogicController::ClientSetShotTypeA_Implementation()
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());
	if (!CurrentHUD)
	{
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("왜 캐스트가 안되는건데, %s"), *GetHUD()->GetName()));
		return;
	}

	CurrentHUD->SetShotTypeA();
}

void AFPSUILogicController::ClientSetShotTypeB_Implementation()
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());
	if (!CurrentHUD)
	{
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("왜 캐스트가 안되는건데, %s"), *GetHUD()->GetName()));
		return;
	}

	CurrentHUD->SetShotTypeB();
}

void AFPSUILogicController::ServerUpdateFriendIdentification_Implementation()
{
	ATDMGameMode* CurrentGameMode = Cast<ATDMGameMode>( UGameplayStatics::GetGameMode(GetWorld()));
	if (!CurrentGameMode)
		return;

	PlayerAccountInfo.GetPartyIndex() == 1 ? CurrentGameMode->UpdateRedTeamDiscrimination() : CurrentGameMode->UpdateBlueTeamDiscrimination();
}

void AFPSUILogicController::ClientUpdateFriendIdentification_Implementation()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFPSUILogicCharacter::StaticClass(), FoundActors);

	for (AActor* FoundActor : FoundActors)
	{
		AFPSUILogicCharacter* UILogicCharacter = Cast<AFPSUILogicCharacter>(FoundActor);
		if (!UILogicCharacter)
			continue;
		
		if (UILogicCharacter->GetCharacterTeamNum() == PlayerAccountInfo.GetPartyIndex())
		{
			UILogicCharacter->ActiveFriendlyIdentification();
		}
	}
}

void AFPSUILogicController::MoveToAnotherServer_Implementation(FName LevelAddress)
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelAddress);
}


void AFPSUILogicController::ClientSetGameModeAndMapName_Implementation(const FText& NewGameModeName,
                                                                       const FText& NewMapName)
{
	ATDMHUD* CurrentHUD = Cast<ATDMHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->SetGameModeAndMapName(NewGameModeName, NewMapName);
}

void AFPSUILogicController::ClientSetPlayerCountInGameReadyWidget_Implementation(int32 PlayerCount, int32 MinimumPlayers)
{
	ATDMHUD* CurrentHUD = Cast<ATDMHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->SetPlayerCountInGameReadyWidget(PlayerCount, MinimumPlayers);
}

void AFPSUILogicController::ClientRemoveGameReadyWidget_Implementation()
{
	ATDMHUD* CurrentHUD = Cast<ATDMHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->RemoveGameReadyWidget();
}

void AFPSUILogicController::ClientSetPartyScore_Implementation(int32 BlueTeamScore, int32 RedTeamScore,
                                                               int32 TargetScore)
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->SetPartyScore(BlueTeamScore, RedTeamScore, TargetScore);
}

void AFPSUILogicController::SetLethalImage_Implementation(UTexture2D* LethalImage)
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->SetLethalImage(LethalImage);
}

void AFPSUILogicController::SetLethalCount_Implementation(int LethalCount)
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->SetLethalCount(LethalCount);
}

void AFPSUILogicController::SetTacticalImage_Implementation(UTexture2D* TacticalImage)
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->SetTacticalImage(TacticalImage);
}

void AFPSUILogicController::SetTacticalCount_Implementation(int TacticalCount)
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->SetTacticalCount(TacticalCount);
}

void AFPSUILogicController::ClientCloseWeaponSelectUI_Implementation()
{
	ADamageFeedbadkHUD* CurrentHUD = Cast<ADamageFeedbadkHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->CloseWeaponSelectUI();
	SetInputMode(FInputModeGameOnly());
	
	
}

void AFPSUILogicController::ClientSetGameStartCoolDown_Implementation(int CoolTime)
{
	ATDMHUD* CurrentHUD = Cast<ATDMHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->SetGamePlayCoolDown(CoolTime);
}

void AFPSUILogicController::ClientRemoveGameStartCoolDown_Implementation()
{
	ATDMHUD* CurrentHUD = Cast<ATDMHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->RemoveGamePlayCoolDownWidget();
}

void AFPSUILogicController::ClientGameEndUI_Implementation(int32 RedTeamScore, int32 BlueTeamScore, bool bIsWin,
	UTexture2D* GameIcon)
{
	ATDMHUD* CurrentHUD = Cast<ATDMHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->InitGameEndUserWidget(RedTeamScore, BlueTeamScore, bIsWin, GameIcon);
}

void AFPSUILogicController::ClientRemoveGameEndUI_Implementation()
{
	ATDMHUD* CurrentHUD = Cast<ATDMHUD>(GetHUD());
	if (!CurrentHUD)
		return;

	CurrentHUD->RemoveGameEndUserWidget();
}

void AFPSUILogicController::ClientFlashHitEffect_Implementation(float Intensity, USoundBase* FlashSound)
{
	UGameplayStatics::PlaySound2D(GetWorld(), FlashSound, Intensity);
	PlayerCameraManager->StartCameraFade(0, 1, Intensity, FLinearColor::White);

	if (FlashTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(FlashTimerHandle);
	}
	
	GetWorldTimerManager().SetTimer(
		FlashTimerHandle,
		this,
		&AFPSUILogicController::FlashHitEffectEnd,
		Intensity,
		false
	);	
}

void AFPSUILogicController::FlashHitEffectEnd()
{
	PlayerCameraManager->StartCameraFade(1, 0, 2, FLinearColor::White);
}