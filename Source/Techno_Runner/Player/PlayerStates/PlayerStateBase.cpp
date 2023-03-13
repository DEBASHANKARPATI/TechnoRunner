// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateBase.h"
#include "JumpState.h"
#include "StrafeState.h"
#include "RotateState.h"
// Sets default values
APlayerStateBase::APlayerStateBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

APlayerStateBase* APlayerStateBase::GetPlayerState(const EPlayerState StateID) const
{
	return PlayerStatesMap[StateID];
}

// Called when the game starts or when spawned
void APlayerStateBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerStatesMap.Add(EPlayerState::E_JUMP, GetWorld()->SpawnActor<AJumpState>(JumpStateAsset));
	PlayerStatesMap.Add(EPlayerState::E_STRAFE, GetWorld()->SpawnActor<AStrafeState>(JumpStateAsset));
	PlayerStatesMap.Add(EPlayerState::E_ROTATE, GetWorld()->SpawnActor<ARotateState>(JumpStateAsset));

}

void APlayerStateBase::Execute(ACharacter* const PlayerCharacter)
{
}

