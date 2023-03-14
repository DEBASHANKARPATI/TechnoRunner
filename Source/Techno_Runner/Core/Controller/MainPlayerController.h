// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"
class AMainPlayer;
class APlayerStateManager;
class APlayerStateBase;
/**
 * Resposible for controlling player inputs 
 */
UCLASS()
class TECHNO_RUNNER_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	void Tick(float DeltaTime) override;
	void BeginPlay() override;
	void SetupInputComponent() override;
	
	UPROPERTY(VisibleAnywhere)
	AMainPlayer* MainPlayer = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlayerStateManager> PlayerStateManagerAsset;

private:

	UFUNCTION()
	void StrafeLeft();
	UFUNCTION()
	void StrafeRight();

	UFUNCTION()
	void TurnLeft();
	UFUNCTION()
	void TurnRight();
	UFUNCTION()
	void Jump();

	const float STRAFE_DISTANCE = 150.0f;
	const float DEGREE_TO_ROTATE = 10.0f;

	FVector LeftStrafeLocation;
	FVector RightStrafeLocation;

	UPROPERTY(VisibleAnywhere)
	APlayerStateManager* PlayerStateManager = nullptr;

	UPROPERTY(VisibleAnywhere)
	APlayerStateBase* CurrentPlayerState = nullptr;
};
