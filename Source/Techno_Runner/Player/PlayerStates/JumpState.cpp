// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpState.h"
#include <GameFramework/Character.h>

void AJumpState::Execute(ACharacter* const TargetCharacter)
{
	TargetCharacter->Jump();
}
