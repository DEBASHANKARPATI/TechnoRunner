// Fill out your copyright notice in the Description page of Project Settings.


#include "PathSpawner.h"

// Sets default values
APathSpawner::APathSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APathSpawner::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void APathSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APathSpawner::CreatePath()
{
	int Stride = 400; // what is the distance between the end and start of a chunk .i.e offset
	int SpawnCount = 100; // how many chunck of path way to create
	int RoatationPoint = 50; // Where will the Path start rotating

	if (PositionList.Num() == 0)// Initial spawning of Spline points
	{
		
		PositionList.Add(GetActorLocation());

		int i = 1;
		while (i != SpawnCount)
		{
			if (i % RoatationPoint == 0)
			{
				SetActorRotation(FRotator(0, GetActorRotation().Yaw + YawRotation[FMath::RandRange(0, 4)], 0));
			}
			FVector NewLocation = FVector(GetActorLocation() + GetActorForwardVector() * Stride);
			//NewLocation.Z = FMath::RandRange(100, -100);
			SetActorLocation(NewLocation);
			PositionList.Add(NewLocation);
			i++;
		}
	}
	else // furthure spawn of spline points 
	{
		float ReplacementPercentage = 0.5f;
		int PreviousSplinePointCount = PositionList.Num();
		SpawnCount = PreviousSplinePointCount * ReplacementPercentage;
		int i = 0;
		while (i != SpawnCount)
		{
			if (PositionList.Num() % RoatationPoint == 0)
			{
				SetActorRotation(FRotator(0, GetActorRotation().Yaw + YawRotation[FMath::RandRange(0, 4)], 0));
			}
			FVector NewLocation = FVector(GetActorLocation() + GetActorForwardVector() * Stride);
			//NewLocation.Z = FMath::RandRange(100, -100);
			SetActorLocation(NewLocation);
			PositionList.Add(NewLocation);
			i++;
		}
	}
}