// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStateBase.h"
#include "RotateState.generated.h"

/**
 * Responsible for rotation state of the player 
 */
UCLASS()
class TECHNO_RUNNER_API ARotateState : public APlayerStateBase
{
	GENERATED_BODY()
public:
	void Initialize(const FRotator Degree);
	void Execute(ACharacter* const TargetCharacter);

private:
	float DegreeToRotate;
	FRotator TargetCharacterRotation = FRotator::ZeroRotator;
};
