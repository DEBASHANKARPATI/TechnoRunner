// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Queue.h"
#include "LevelSpawner.generated.h"

class USplineComponent;
class USplineMeshComponent;
class APathSpawner;

UCLASS()
class TECHNO_RUNNER_API ALevelSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	USplineComponent* PathSpawnerSpline;
	
	//TODO: Later this mesh will come from a structure 
	//Which will be stored in a object pool 

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* PathMesh; 

	UPROPERTY(EditDefaultsOnly)
	UMaterial* PathMaterial;

	UPROPERTY(EditDefaultsOnly)
	int16 SegmentLength = 400;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	//TArray<USplineMeshComponent*> SplineMeshComponents;
	TArray<USplineMeshComponent*> SplineMeshComponentList;

	UFUNCTION()
	void SpawnChunk(float Diatance);

	UPROPERTY(EditAnywhere)
	APathSpawner* PathSpawner;

	UFUNCTION()
	void ExtendPath();

	float CurrentDistance = 0;
};
