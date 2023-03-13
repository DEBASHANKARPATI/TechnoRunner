// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerStateBase.h"
#include "StrafeState.generated.h"

/**
 * Responsible for Strafe state of the character
 */
UCLASS()
class TECHNO_RUNNER_API AStrafeState : public APlayerStateBase
{
	GENERATED_BODY()
public:
	void Initialize(const FVector& InStafeLocation);
	void Execute(ACharacter* const Charcater);

private:
	FVector StrafeLocation;
};
