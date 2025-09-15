// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BaseGM.h"

FString ACPP_BaseGM::GetClientIPAddress(APlayerController* PlayerController)
{
    if (PlayerController && PlayerController->GetNetConnection())
    {
        FString IP = PlayerController->GetNetConnection()->RemoteAddressToString();
        return IP;
    }
    return TEXT("Unknown IP");
}

FString ACPP_BaseGM::GetClientPCName(APlayerController* PlayerController)
{
    
    return FPlatformMisc::GetDeviceId();
}

void ACPP_BaseGM::Logout(AController* Exiting)
{
    //UE_LOG(LogTemp, Display, TEXT("Override Logout Function Execution"));
    //if (APlayerController* PC = Cast<APlayerController>(Exiting))
    //{
    //    /*
    //    
    //    UE_LOG(LogTemp, Display, TEXT("Player PC UnPossess"));
    //    PC->UnPossess();
    //    
    //    */
    //    
    //    if (APawn* PlayerPawn = PC->GetPawn())
    //    {
    //        UE_LOG(LogTemp, Display, TEXT("Pawn DetachFromControllerPendingDestroy"));
    //        // 캐릭터가 삭제되지 않도록 컨트롤러와의 연결만 해제
    //        PlayerPawn->DetachFromControllerPendingDestroy();
    //    }
    //    else
    //    {
    //        UE_LOG(LogTemp, Warning, TEXT("PC->GetPawn() is nullptr"));
    //    }
    //    
    //}

    Super::Logout(Exiting);
}





