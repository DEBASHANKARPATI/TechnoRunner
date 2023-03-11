// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelEditor.h"
#include <Components/SplineComponent.h>
#include <Components/SplineMeshComponent.h>
#include "SplinePointGenerator.h"
// Sets default values
ALevelEditor::ALevelEditor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelEditor::BeginPlay()
{
	Super::BeginPlay();
	if (SplinePointGeneratorAsset)
	{
		if (const auto World = GetWorld())
		{
			SplinePointGenerator = World->SpawnActor<ASplinePointGenerator>(SplinePointGeneratorAsset);
			SplinePointGenerator->SetActorLocation(FVector(0, 0, 0));
		}
	}
}

// Called every frame
void ALevelEditor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



