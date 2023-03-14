// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateManager.h"

// Sets default values
APlayerStateManager::APlayerStateManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

APlayerStateBase* APlayerStateManager::GetPlayerState(const EPlayerState StateID) const
{
	return PlayerStatesMap[StateID];
}

void APlayerStateManager::ExecuteState(ACharacter* const Character , bool bCanLoop)
{
	FTimerDelegate StateDelegate;
	StateDelegate.BindUObject(this, &ThisClass::Execute_Internal, Character);

	if (bCanLoop)
	{
		GetWorldTimerManager().SetTimer(StateTimer, StateDelegate, GetWorld()->GetDeltaSeconds(), true);
	}
	else
	{
		GetWorldTimerManager().SetTimer(StateTimer, StateDelegate,0.0f,false);
	}
}

void APlayerStateManager::Execute_Internal(ACharacter* const Character)
{
	if (CurrentState)
	{
		CurrentState->Execute(Character);
	}
}

// Called when the game starts or when spawned
void APlayerStateManager::BeginPlay()
{
	Super::BeginPlay();
	if (JumpStateAsset)
	{
		JumpState = Cast<AJumpState>(GetWorld()->SpawnActor(JumpStateAsset));
		if (JumpState)
		{
			PlayerStatesMap.Add(EPlayerState::E_JUMP, JumpState);
		}
	}
	if (StrafeStateAsset)
	{
		StrafeState = Cast<AStrafeState>(GetWorld()->SpawnActor(StrafeStateAsset));
		if (StrafeState)
		{
			PlayerStatesMap.Add(EPlayerState::E_STRAFE, StrafeState);
		}
	}
	if (RotateStateAsset)
	{
		RotateState = Cast<ARotateState>(GetWorld()->SpawnActor<ARotateState>(RotateStateAsset));
		if (RotateState)
		{
			PlayerStatesMap.Add(EPlayerState::E_ROTATE, RotateState);
		}
	}
	
}

