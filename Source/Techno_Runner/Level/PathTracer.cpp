// Fill out your copyright notice in the Description page of Project Settings.


#include "PathTracer.h"

// Sets default values
APathTracer::APathTracer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APathTracer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APathTracer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void APathTracer::GeneratePathPoints(TArray<FVector>& PositionList , int SpawnCount)
{
	int Stride = 400; // what is the distance between the end and start of a chunk .i.e offset
	int RoatationPoint = 50; // offset for rotation

	PositionList.Add(GetActorLocation());

	int i = PositionList.Num();
	int TotalPointsToSpawn = i + SpawnCount;
	while (i != TotalPointsToSpawn)
	{
		if (i % RoatationPoint == 0)
		{
			SetActorRotation(FRotator(0, GetActorRotation().Yaw + YawRotation[FMath::RandRange(0, 4)], 0));
		}

		FVector NewLocation = FVector(GetActorLocation() + GetActorForwardVector() * Stride);
		SetActorLocation(NewLocation);
		PositionList.Add(NewLocation);
		i++;
	}
}
