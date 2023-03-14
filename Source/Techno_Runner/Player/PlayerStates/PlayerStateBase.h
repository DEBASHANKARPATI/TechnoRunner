// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerStateBase.generated.h"
class ACharacter;

/// <summary>
/// Acts as a base class for all the states for player to be in  
/// </summary>


UCLASS()
class TECHNO_RUNNER_API APlayerStateBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerStateBase();
	virtual void Execute(ACharacter* const PlayerCharacter);
};
