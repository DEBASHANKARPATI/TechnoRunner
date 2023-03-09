// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSpawner.h"
#include <Components/SplineComponent.h>
#include <Components/SplineMeshComponent.h>
#include "PathSpawner.h"
// Sets default values
ALevelSpawner::ALevelSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!PathSpawnerSpline)
	{
		PathSpawnerSpline = CreateDefaultSubobject<USplineComponent>("PathSpawnerSplineComponent");
		if (PathSpawnerSpline)
		{
			this->SetRootComponent(PathSpawnerSpline);
			PathSpawnerSpline->SetRelativeLocation(FVector::ZeroVector);
			PathSpawnerSpline->SetRelativeScale3D(FVector::One());
		}
	}

}

// Called when the game starts or when spawned
void ALevelSpawner::BeginPlay()
{
	Super::BeginPlay();
	if (PathSpawner)
	{
		PathSpawner->CreatePath();
	}
	for (int i=0;i< PathSpawner->PositionList.Num();i++)
	{
		PathSpawnerSpline->AddSplineLocalPoint(PathSpawner->PositionList[i]);
	}

	int i = 0;
	while (CurrentDistance < PathSpawnerSpline->GetSplineLength())
	{
       SpawnChunk(FMath::Min(CurrentDistance,PathSpawnerSpline->GetSplineLength()));
	   CurrentDistance += SegmentLength;
	}
	FTimerHandle SpawnTimer;
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ALevelSpawner::ExtendPath, 10.0f, true);
}

// Called every frame
void ALevelSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSpawner::SpawnChunk(float Distance)
{
	USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(this);
	SplineMesh->RegisterComponent();
	SplineMesh->SetMobility(EComponentMobility::Movable);

	FVector StartPosition = PathSpawnerSpline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);
	FVector EndPosition = PathSpawnerSpline->GetLocationAtDistanceAlongSpline(Distance + SegmentLength, ESplineCoordinateSpace::Local);

	FVector StartTangent = PathSpawnerSpline->GetTangentAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);
	FVector EndTangent = PathSpawnerSpline->GetTangentAtDistanceAlongSpline(Distance + SegmentLength, ESplineCoordinateSpace::Local);


	FVector2D StartScale = FVector2D(PathSpawnerSpline->GetScaleAtDistanceAlongSpline(Distance));
	FVector2D EndScale = FVector2D(PathSpawnerSpline->GetScaleAtDistanceAlongSpline(Distance + SegmentLength));

	SplineMesh->SetStartAndEnd(StartPosition, StartTangent, EndPosition, EndTangent);
	SplineMesh->SetStartScale(StartScale);
	SplineMesh->SetEndScale(StartScale);

	SplineMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SplineMesh->SetStaticMesh(PathMesh);
	SplineMesh->SetMaterial(0, PathMaterial);
	SplineMesh->SetForwardAxis(ESplineMeshAxis::X);
	SplineMesh->AttachToComponent(PathSpawnerSpline, FAttachmentTransformRules::FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	SplineMeshComponentList.Add(SplineMesh);
}

void ALevelSpawner::ExtendPath()
{
	//TODO :  Instead of Removing and adding spline meshes write an object pool for recycling the meshes Everytime we extend path way .
	//Give proper Naming conventions 


	int PreviousCount = PathSpawner->PositionList.Num();
	CurrentDistance = PathSpawnerSpline->GetSplineLength();

	//Appending the path points
	PathSpawner->CreatePath();// Creates some percentage of path to the existing path 

	for (int i = PreviousCount ; i < PathSpawner->PositionList.Num(); i++)
	{
		PathSpawnerSpline->AddSplineLocalPoint(PathSpawner->PositionList[i]);
	}

	while (CurrentDistance < PathSpawnerSpline->GetSplineLength())
	{
		SpawnChunk(FMath::Min(CurrentDistance, PathSpawnerSpline->GetSplineLength()));
		CurrentDistance += SegmentLength;
	}

	//Removing path points
	int NumberOfPointsToRemove = 10;
	for (int i = 0; i < NumberOfPointsToRemove; i++)
	{
		//SplineMeshComponents[i]->bHiddenInGame = true;
		//SplineMeshComponents[i]->DetachFromParent();
		USplineMeshComponent* ElementToRemove;
		ElementToRemove = *SplineMeshComponentList.begin();
		SplineMeshComponentList.Remove(ElementToRemove);
		ElementToRemove->DestroyComponent();


		PathSpawnerSpline->RemoveSplinePoint(i);

	}
	
}
