// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include <Techno_Runner/Player/MainPlayer.h>
#include <Techno_Runner/Player/PlayerStates/PlayerStateManager.h>
//#include <Techno_Runner/Player/PlayerStates/JumpState.h>
#include <Techno_Runner/Player/PlayerStates/RotateState.h>
#include <Techno_Runner/Player/PlayerStates/StrafeState.h>

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (CurrentPlayerState && MainPlayer)
	//{
	//	CurrentPlayerState->Execute(Cast<ACharacter>(MainPlayer));
	//}
}
void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!MainPlayer)
	{
		MainPlayer = Cast<AMainPlayer>(GetPawn());
	}
	if (PlayerStateManagerAsset)
	{
		PlayerStateManager = GetWorld()->SpawnActor<APlayerStateManager>(PlayerStateManagerAsset);
	}
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("StrafeLeft", IE_Pressed, this, &AMainPlayerController::StrafeLeft);
	InputComponent->BindAction("StrafeRight", IE_Pressed, this, &AMainPlayerController::StrafeRight);
	InputComponent->BindAction("RotateRight", IE_Pressed, this, &AMainPlayerController::TurnLeft);
	InputComponent->BindAction("RotateLeft", IE_Pressed, this, &AMainPlayerController::TurnRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMainPlayerController::Jump);
}

void AMainPlayerController::StrafeLeft()
{
	if (MainPlayer)
	{
		LeftStrafeLocation = -1 * MainPlayer->GetActorRightVector() * STRAFE_DISTANCE ;
		PlayerStateManager->InitializeState(E_STRAFE, LeftStrafeLocation.ToString());
		PlayerStateManager->ExecuteState(MainPlayer, true);
	}
}

void AMainPlayerController::StrafeRight()
{
	if (MainPlayer)
	{
		RightStrafeLocation = MainPlayer->GetActorRightVector() * STRAFE_DISTANCE;
		PlayerStateManager->InitializeState(E_STRAFE, RightStrafeLocation.ToString());
		PlayerStateManager->ExecuteState(MainPlayer, true);
	}
}

void AMainPlayerController::TurnLeft()
{
	if (MainPlayer)
	{ 
		FRotator TargetRotation = MainPlayer->GetActorRotation();
		TargetRotation.Yaw += (-DEGREE_TO_ROTATE);
		PlayerStateManager->InitializeState(E_ROTATE,TargetRotation.ToString());
		PlayerStateManager->ExecuteState(MainPlayer, true);
	}
}

void AMainPlayerController::TurnRight()
{
	if (MainPlayer)
	{
		FRotator TargetRotation = MainPlayer->GetActorRotation();
		TargetRotation.Yaw += (DEGREE_TO_ROTATE);
		PlayerStateManager->InitializeState(E_ROTATE, TargetRotation.ToString());
		PlayerStateManager->ExecuteState(MainPlayer, true);
	}
}

void AMainPlayerController::Jump()
{
	if (MainPlayer)
	{
		PlayerStateManager->InitializeState(E_JUMP);
		PlayerStateManager->ExecuteState(MainPlayer, false);
	}
}
