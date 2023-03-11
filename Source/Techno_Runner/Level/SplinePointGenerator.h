// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplinePointGenerator.generated.h"
class USplineComponent;
class USplineMeshComponent;

/// <summary>
/// Responsible for Creating spline points and populating the spline with Mesh and props 
/// </summary>
class APathTracer;
class AMainPlayer;

UCLASS()
class TECHNO_RUNNER_API ASplinePointGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplinePointGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		//TArray<USplineMeshComponent*> SplineMeshComponents;
	TArray<USplineMeshComponent*> SplineMeshComponentList;

	UPROPERTY(EditDefaultsOnly)
	USplineComponent* PathSpline;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* PathMesh;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* PathMaterial;

	UPROPERTY(EditDefaultsOnly)
	int16 SegmentLength = 400;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APathTracer> PathTracerAsset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	UPROPERTY(VisibleAnywhere)
	TArray<FVector> PositionList;

	void SpawnChunk(float Distance);

	void RecyclePathPoints();

	void OnDesiredDistanceCovered(bool bWasSuccessful);
private:
	float CurrentDistance = 0;

	UPROPERTY(VisibleAnywhere)
	APathTracer* PathTracer;

	UPROPERTY(VisibleAnywhere)
	AMainPlayer* MainPlayer;


};
