// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathTracer.generated.h"
/// <summary>
/// Traces Path for geerating input points to the spline 
/// </summary>
UCLASS()
class TECHNO_RUNNER_API APathTracer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APathTracer();

	/// <summary>
	/// Generates path points and populate the PositionList 
	/// </summary>
	/// <param name="PositionList"> Container to fill newly generated points </param>
	/// <param name="SpawnCount"> Number of positions to generate </param>
	
	void GeneratePathPoints(TArray<FVector>& PositionList , int SpawnCount = 100);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	TArray<float> YawRotation{ -10.0f , 10.0f , 0.0f , 0.0f , 0.0f };

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	int RotationTriggerCounter = 1;
};
