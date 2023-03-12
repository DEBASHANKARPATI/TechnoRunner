// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Queue.h"
#include "LevelEditor.generated.h"
class ASplinePointGenerator;

/// <summary>
/// Responsible for generating level proccedurally
/// </summary>

UCLASS()
class TECHNO_RUNNER_API ALevelEditor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelEditor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASplinePointGenerator> SplinePointGeneratorAsset;

	ASplinePointGenerator* GetSplinePointGenerator() const;

private:
	UPROPERTY(VisibleAnywhere)
	ASplinePointGenerator* SplinePointGenerator;
	
};
