// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/FPSMovementLogicController.h"

#include "Character/FPSMovementLogicCharacter.h"

void AFPSMovementLogicController::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSMovementLogicController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSMovementLogicController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("Turn", this, &AFPSMovementLogicController::Turn);
	InputComponent->BindAxis("LookUp", this, &AFPSMovementLogicController::LookUp);
	InputComponent->BindAxis("MoveForward", this, &AFPSMovementLogicController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFPSMovementLogicController::MoveRight);

	InputComponent->BindAction("Jump", IE_Pressed ,this, &AFPSMovementLogicController::JumpPressed);
	InputComponent->BindAction("Jump", IE_Released ,this, &AFPSMovementLogicController::JumpReleased);
	
	InputComponent->BindAction("Run", IE_Pressed ,this, &AFPSMovementLogicController::RunPressed);
	InputComponent->BindAction("Run", IE_Released,this, &AFPSMovementLogicController::RunReleased);

	InputComponent->BindAction("Crouch", IE_Pressed ,this, &AFPSMovementLogicController::Crouch);
	InputComponent->BindAction("Prone", IE_Pressed ,this, &AFPSMovementLogicController::Prone);
}

AFPSMovementLogicCharacter* AFPSMovementLogicController::GetMovementLogicCharacter() const
{
	return Cast<AFPSMovementLogicCharacter>(GetPawn());
}


void AFPSMovementLogicController::Turn(const float AxisValue)
{
	if (bIsPlayerAlive)
	{
		if (GetMovementLogicCharacter())
		{
			GetMovementLogicCharacter()->Turn(AxisValue);
		}
	}	
}

void AFPSMovementLogicController::LookUp(const float AxisValue)
{
	if (bIsPlayerAlive)
	{
		if (GetMovementLogicCharacter())
		{
			GetMovementLogicCharacter()->LookUp(AxisValue);
		}
	}	
}

void AFPSMovementLogicController::MoveForward(const float AxisValue)
{
	if (!bIsCanWork || !bIsPlayerAlive)
		return;
	
	if (GetMovementLogicCharacter())
	{
		ForwardBackAxis = AxisValue;
		GetMovementLogicCharacter()->MoveForwardBack(AxisValue);
	}
}

void AFPSMovementLogicController::MoveRight(const float AxisValue)
{
	if (!bIsCanWork || !bIsPlayerAlive)
		return;
	
	if (GetMovementLogicCharacter())
	{
		LeftRightAxis = AxisValue;
		GetMovementLogicCharacter()->MoveLeftRight(AxisValue);
	}
}

void AFPSMovementLogicController::JumpPressed()
{
	if (!bIsCanWork || !bIsPlayerAlive)
		return;

	if (GetMovementLogicCharacter())
	{
		GetMovementLogicCharacter()->JumpStart();
	}
}

void AFPSMovementLogicController::JumpReleased()
{
	if (!bIsCanWork || !bIsPlayerAlive)
		return;

	if (GetMovementLogicCharacter())
	{
		GetMovementLogicCharacter()->JumpStop();
	}
}

void AFPSMovementLogicController::RunPressed()
{
	if (!bIsCanWork)
		return;

	if (GetMovementLogicCharacter())
	{
		GetMovementLogicCharacter()->ServerStartRun();
	}
}

void AFPSMovementLogicController::RunReleased()
{
	if (!bIsCanWork)
		return;

	if (GetMovementLogicCharacter())
	{
		GetMovementLogicCharacter()->ServerStopRun();
	}
}

void AFPSMovementLogicController::Crouch()
{
	if (!bIsPlayerAlive)
		return;

	if (GetMovementLogicCharacter())
	{
		GetMovementLogicCharacter()->ServerCrouch();
	}

		
}

void AFPSMovementLogicController::Prone()
{
	if (!bIsCanWork || !bIsPlayerAlive)
		return;

	if (GetMovementLogicCharacter())
	{
		GetMovementLogicCharacter()->ServerProne();
	}
}
