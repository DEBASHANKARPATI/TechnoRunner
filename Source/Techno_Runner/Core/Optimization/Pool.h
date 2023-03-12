// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <GameFramework/Actor.h>
#include "CoreMinimal.h"
#include "Pool.generated.h"
class USplineMeshComponent;
class USplineComponent;
class UMaterial;
class UStaticMesh;

/**
 * Used for caching pool of objects which needs to be destroyed and created repeatatively
 */
UCLASS()
class TECHNO_RUNNER_API APool : public AActor
{
	GENERATED_BODY()

public:
	APool();
	void InstantiateSplineMeshes(USplineComponent* const TargetSpline ,UMaterial* const InMaterial , UStaticMesh* const InStaticMesh , int SegmentLength);
	TArray<USplineMeshComponent*> GetSplineMeshPool();
	void RecycleSplineMeshes(USplineComponent* const TargetSpline, float PreviousSplineLength, UMaterial* const InMaterial, UStaticMesh* const InStaticMesh, int SegmentLength, int Count);

private:
	UPROPERTY(VisibleAnywhere)
	TArray<USplineMeshComponent*> SplineMeshComponentList;
};
