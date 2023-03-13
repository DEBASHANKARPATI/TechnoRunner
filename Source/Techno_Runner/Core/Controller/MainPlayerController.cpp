// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include <Techno_Runner/Player/MainPlayer.h>
#include <Techno_Runner/Player/PlayerStates/PlayerStateBase.h>
//#include <Techno_Runner/Player/PlayerStates/JumpState.h>
#include <Techno_Runner/Player/PlayerStates/RotateState.h>
#include <Techno_Runner/Player/PlayerStates/StrafeState.h>

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentPlayerState && MainPlayer)
	{
		CurrentPlayerState->Execute(Cast<ACharacter>(MainPlayer));
	}
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!MainPlayer)
	{
		MainPlayer = Cast<AMainPlayer>(GetPawn());
	}
	if (!PlayerStateBase)
	{
		PlayerStateBase = GetWorld()->SpawnActor<APlayerStateBase>(PlayerStateBaseAsset);
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
		AStrafeState* StrafeState = Cast<AStrafeState>(PlayerStateBase->GetPlayerState(E_STRAFE));
		StrafeState->Initialize(LeftStrafeLocation);
		CurrentPlayerState = Cast<APlayerStateBase>(StrafeState);
	}
}

void AMainPlayerController::StrafeRight()
{
	if (MainPlayer)
	{
		RightStrafeLocation = MainPlayer->GetActorRightVector() * STRAFE_DISTANCE;
		AStrafeState* StrafeState = Cast<AStrafeState>(PlayerStateBase->GetPlayerState(E_STRAFE));
		StrafeState->Initialize(LeftStrafeLocation);
		CurrentPlayerState = Cast<APlayerStateBase>(StrafeState);
	}
}

void AMainPlayerController::TurnLeft()
{
	if (MainPlayer)
	{
		ARotateState* RotateState = Cast<ARotateState>(PlayerStateBase->GetPlayerState(E_ROTATE));
		RotateState->Initialize(-DEGREE_TO_ROTATE);
		CurrentPlayerState = Cast<APlayerStateBase>(RotateState);
	}
}

void AMainPlayerController::TurnRight()
{
	if (MainPlayer)
	{
		ARotateState* RotateState = Cast<ARotateState>(PlayerStateBase->GetPlayerState(E_ROTATE));
		RotateState->Initialize(DEGREE_TO_ROTATE);
		CurrentPlayerState = Cast<APlayerStateBase>(RotateState);
	}
}

void AMainPlayerController::Jump()
{
	if (MainPlayer)
	{
		MainPlayer->Jump();
	}
}
