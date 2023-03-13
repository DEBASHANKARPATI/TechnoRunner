// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerStateBase.generated.h"
class ACharacter;
class AJumpState;
class AStrafeState;
class ARotateState;

/// <summary>
/// Acts as a base class for all the states for player to be in  
/// </summary>
UENUM()
enum EPlayerState
{
    E_JUMP,
	E_STRAFE,
	E_ROTATE
};

UCLASS()
class TECHNO_RUNNER_API APlayerStateBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerStateBase();
	APlayerStateBase* GetPlayerState(const EPlayerState StateID) const;
	virtual void Execute(ACharacter* const PlayerCharacter);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStrafeState> StrafeStateAsset;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ARotateState> RotateStateAsset;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AJumpState> JumpStateAsset;

private:
	TMap<TEnumAsByte<EPlayerState>,APlayerStateBase*> PlayerStatesMap; //Map contains states Mapped by state names 


};
