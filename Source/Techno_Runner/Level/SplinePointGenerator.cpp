// Fill out your copyright notice in the Description page of Project Settings.


#include "SplinePointGenerator.h"
#include <Components/SplineComponent.h>
#include <Components/SplineMeshComponent.h>
#include <Techno_Runner/Level/PathTracer.h>
#include <Techno_Runner/Core/Controller/MainPlayerController.h>
#include <Techno_Runner/Player/MainPlayer.h>
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

		if (PathTracerAsset)
		{
			if (const auto PathTracerClone = World->SpawnActor<APathTracer>(PathTracerAsset))
			{
				PathTracer = PathTracerClone;
				PathTracer->GeneratePathPoints(PositionList);

				for (int i = 0; i < PositionList.Num(); i++)
				{
					PathSpline->AddSplineLocalPoint(PositionList[i]);
				}

				int i = 0;
				while (CurrentDistance < PathSpline->GetSplineLength())
				{
					SpawnChunk(FMath::Min(CurrentDistance, PathSpline->GetSplineLength()));
					CurrentDistance += SegmentLength;
				}
				/*FTimerHandle SpawnTimer;
				GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASplinePointGenerator::RecyclePathPoints, 2.5f, true);*/
			}
		}
	}

	
}

// Called every frame
void ASplinePointGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//RecyclePathPoints();
}

void ASplinePointGenerator::SpawnChunk(float Distance)
{
	//Optimize this using Object pool
	USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(this);
	SplineMesh->RegisterComponent();
	SplineMesh->SetMobility(EComponentMobility::Movable);

	FVector StartPosition = PathSpline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);
	FVector EndPosition = PathSpline->GetLocationAtDistanceAlongSpline(Distance + SegmentLength, ESplineCoordinateSpace::Local);

	FVector StartTangent = PathSpline->GetTangentAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);
	FVector EndTangent = PathSpline->GetTangentAtDistanceAlongSpline(Distance + SegmentLength, ESplineCoordinateSpace::Local);


	FVector2D StartScale = FVector2D(PathSpline->GetScaleAtDistanceAlongSpline(Distance));
	FVector2D EndScale = FVector2D(PathSpline->GetScaleAtDistanceAlongSpline(Distance + SegmentLength));

	SplineMesh->SetStartAndEnd(StartPosition, StartTangent, EndPosition, EndTangent);
	SplineMesh->SetStartScale(StartScale);
	SplineMesh->SetEndScale(StartScale);

	SplineMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SplineMesh->SetStaticMesh(PathMesh);
	SplineMesh->SetMaterial(0, PathMaterial);
	SplineMesh->SetForwardAxis(ESplineMeshAxis::X);
	SplineMesh->AttachToComponent(PathSpline, FAttachmentTransformRules::FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	SplineMeshComponentList.Add(SplineMesh);
}

void ASplinePointGenerator::RecyclePathPoints()
{
	int PreviousCount = PositionList.Num();
	CurrentDistance = PathSpline->GetSplineLength();


	//float DistanceCoveredByPlayerAlongSpline = FVector::Distance(PathSpline->GetWorldLocationAtDistanceAlongSpline(0) ,  MainPlayer->GetActorLocation());
	int NumberOfSplinePoints = 1; //floor(DistanceCoveredByPlayerAlongSpline / SegmentLength);

	//Appending the path points
	PathTracer->GeneratePathPoints(PositionList , NumberOfSplinePoints);// Creates some percentage of path to the existing path 

	for (int i = PreviousCount; i < PositionList.Num(); i++)
	{
		PathSpline->AddSplineLocalPoint(PositionList[i]);
	}

	while (CurrentDistance < PathSpline->GetSplineLength())
	{
		SpawnChunk(FMath::Min(CurrentDistance, PathSpline->GetSplineLength()));
		CurrentDistance += SegmentLength;
	}

	//Removing path points
	for (int i = 0; i < NumberOfSplinePoints; i++)
	{
		USplineMeshComponent* ElementToRemove;
		ElementToRemove = *SplineMeshComponentList.begin();
		SplineMeshComponentList.Remove(ElementToRemove);
		ElementToRemove->DestroyComponent();
		PathSpline->RemoveSplinePoint(i);
	}
}

void ASplinePointGenerator::OnDesiredDistanceCovered(bool bWasSuccessful)
{
	RecyclePathPoints();
}
