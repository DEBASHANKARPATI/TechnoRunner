// Fill out your copyright notice in the Description page of Project Settings.
#include "SplinePointGenerator.h"
#include <Components/SplineComponent.h>
#include <Components/SplineMeshComponent.h>
#include <Techno_Runner/Level/PathTracer.h>
#include <Techno_Runner/Core/Controller/MainPlayerController.h>
#include <Techno_Runner/Player/MainPlayer.h>
#include <Techno_Runner/Core/Optimization/Pool.h>
#include <Techno_Runner/Core/GameInstance/TechnoRunnerGameInstance.h>

// Sets default values
ASplinePointGenerator::ASplinePointGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!PathSpline)
	{
		PathSpline = CreateDefaultSubobject<USplineComponent>("PathSpawnerSplineComponent");
		if (PathSpline)
		{
			PathSpline->SetRelativeLocation(FVector::ZeroVector);
			PathSpline->SetRelativeScale3D(FVector::One());
		}
	}
}

// Called when the game starts or when spawned
void ASplinePointGenerator::BeginPlay()
{
	Super::BeginPlay();

	if (const auto World = GetWorld())
	{
		if (const AMainPlayerController* MainPlayerController = Cast<AMainPlayerController>(World->GetFirstPlayerController()))
		{
			if (AMainPlayer* MainPlayerClone = Cast<AMainPlayer>(MainPlayerController->GetPawn()))
			{
				MainPlayer = MainPlayerClone;
				MainPlayer->OnDesiredDistanceCovered.AddUObject(this,&ThisClass::OnDesiredDistanceCovered);
			}
		}

		if (const auto GameInstance = Cast<UTechnoRunnerGameInstance>(World->GetGameInstance()))
		{
			ObjectPool = GameInstance->GetPool();
		}

		if (PathTracerAsset)
		{
			if (const auto PathTracerClone = World->SpawnActor<APathTracer>(PathTracerAsset))
			{
				PathTracer = PathTracerClone;
				PathTracer->GeneratePathPoints(PositionList,50);

				for (int i = 0; i < PositionList.Num(); i++)
				{
					PathSpline->AddSplineLocalPoint(PositionList[i]);
				}

				ObjectPool->InstantiateSplineMeshes(PathSpline,PathMaterial,PathMesh,SegmentLength);
			}
		}
	}
}

// Called every frame
void ASplinePointGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASplinePointGenerator::RecyclePathPoints()
{
	int PreviousCount = PositionList.Num();
	float PreviousSplineLength = PathSpline->GetSplineLength();

	int NumberOfSplinePoints = 1; //floor(DistanceCoveredByPlayerAlongSpline / SegmentLength);

	//Appending the path points
	PathTracer->GeneratePathPoints(PositionList , NumberOfSplinePoints);// Creates some percentage of path to the existing path 

	for (int i = PreviousCount; i < PositionList.Num(); i++)
	{
		PathSpline->AddSplineLocalPoint(PositionList[i]);
	}

	ObjectPool->RecycleSplineMeshes(PathSpline , PreviousSplineLength , PathMaterial , PathMesh , SegmentLength , NumberOfSplinePoints);

	for (int i = 0; i < NumberOfSplinePoints; i++)
	{
		PathSpline->RemoveSplinePoint(i);
	}
}

void ASplinePointGenerator::OnDesiredDistanceCovered(bool bWasSuccessful)
{
	RecyclePathPoints();
}

int ASplinePointGenerator::GetSegmentLength() const
{
	return SegmentLength;
}

USplineComponent* ASplinePointGenerator::GetSplineComponent() const
{
	return PathSpline;
}
