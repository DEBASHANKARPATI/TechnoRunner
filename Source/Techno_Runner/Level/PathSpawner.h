// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathSpawner.generated.h"

UCLASS()
class TECHNO_RUNNER_API APathSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APathSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	TArray<FVector> PositionList;

	UPROPERTY(EditAnywhere)
	TArray<float> YawRotation{-90.0f , 90.0f , 0.0f , 0.0f , 0.0f};

	void CreatePath();

};
