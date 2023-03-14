// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerStateBase.h"
#include "JumpState.h"
#include "StrafeState.h"
#include "RotateState.h"
#include "PlayerStateManager.generated.h"

UENUM()
enum EPlayerState
{
	E_NONE,
	E_JUMP,
	E_STRAFE,
	E_ROTATE
};

UCLASS()
class TECHNO_RUNNER_API APlayerStateManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerStateManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStrafeState> StrafeStateAsset;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ARotateState> RotateStateAsset;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AJumpState> JumpStateAsset;

public:	
	template<typename T>
	void InitializeState(const EPlayerState StateID, T InitializationParameter)
	{
		switch (StateID)
		{
		case E_JUMP:
		{
			CurrentState = Cast<AJumpState>(PlayerStatesMap[E_JUMP]);
			break;
		}
		case E_ROTATE:
		{
			FRotator TargetRotation = (InitializationParameter); 
			ARotateState* RotateStateTemp = Cast<ARotateState>(PlayerStatesMap[E_ROTATE]);
			CurrentState = RotateState;
			if (RotateState)
			{
				RotateState->Initialize(TargetRotation);
			}
			break;
		}
		case E_STRAFE:
		{
			FVector TargetVector = (InitializationParameter);
			AStrafeState* StrafeStateTemp = Cast<AStrafeState>(PlayerStatesMap[E_STRAFE]);
			CurrentState = StrafeState;
			if(StrafeState)
			{
				StrafeState->Initialize(TargetVector);
			}
			break;
		}
		default:
			break;
		}
	}

	APlayerStateBase* GetPlayerState(const EPlayerState PlayerStateID) const;
	void ExecuteState(ACharacter* const Character , bool bCanLoop = true);

private:
	TMap<TEnumAsByte<EPlayerState>, APlayerStateBase*> PlayerStatesMap; //Map contains states Mapped by state names 

	AJumpState* JumpState = nullptr;
	AStrafeState* StrafeState = nullptr;
	ARotateState* RotateState = nullptr;

	APlayerStateBase* CurrentState = nullptr;

	UFUNCTION()
	void Execute_Internal(ACharacter* const Character);

	FTimerHandle StateTimer;
};
