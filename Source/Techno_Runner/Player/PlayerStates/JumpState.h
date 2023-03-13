// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStateBase.h"
#include "JumpState.generated.h"
class ACharacter;
/**
 * Responsible for Jump state of player 
 */
UCLASS()
class TECHNO_RUNNER_API AJumpState : public APlayerStateBase
{
	GENERATED_BODY()

public:
	void Execute(ACharacter* const TargetCharacter) override;
	
};
