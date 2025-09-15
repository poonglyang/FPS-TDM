// Fill out your copyright notice in the Description page of Project Settings.
#include "GetPlayerAddress.h"

FString UGetPlayerAddress::GetClientIPAddress(APlayerController* PlayerController)
{
    if (PlayerController && PlayerController->GetNetConnection())
    {
        FString IP = PlayerController->GetNetConnection()->RemoteAddressToString();
        return IP;
    }
    return TEXT("Unknown IP");
}
