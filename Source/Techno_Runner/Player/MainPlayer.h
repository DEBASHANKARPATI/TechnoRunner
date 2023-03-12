// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"
class UCharacterMovementComponent;
class ASplinePointGenerator;
DECLARE_MULTICAST_DELEGATE_OneParam (FOnDesiredDistanceCovered , bool);
UCLASS()
class TECHNO_RUNNER_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayer();
	FOnDesiredDistanceCovered OnDesiredDistanceCovered;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float DistanceCovered = 0.0f;

private:
	UCharacterMovementComponent* CharacterMovementComponent = nullptr;
	ASplinePointGenerator* SplineGenerator;

};
