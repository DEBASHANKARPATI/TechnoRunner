// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Techno_Runner/Core/GameInstance/TechnoRunnerGameInstance.h> 
#include <Techno_Runner/Level/LevelEditor.h>
#include <Techno_Runner/Level/SplinePointGenerator.h>
#include <Components/SplineComponent.h>

// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (const UWorld* World = GetWorld())
	{
		if (const UTechnoRunnerGameInstance* GameInstance = Cast<UTechnoRunnerGameInstance>(GetWorld()->GetGameInstance()))
		{
			if (const auto LevelEditor = GameInstance->GetLevelEditor())
			{
				SplineGenerator = LevelEditor->GetSplinePointGenerator();
			}
		}
	}


	if (const auto CharacterMovementComponentClone =GetCharacterMovement())
	{
		CharacterMovementComponent = CharacterMovementComponentClone;
	}
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CharacterMovementComponent && CharacterMovementComponent->IsMovingOnGround())
	{
		DistanceCovered += CharacterMovementComponent->Velocity.Length() * DeltaTime;
		AddMovementInput(GetActorForwardVector(), DistanceCovered);
		if (DistanceCovered > 400)
		{
			DistanceCovered = 0.0f;
			if (OnDesiredDistanceCovered.IsBound())
			{
				OnDesiredDistanceCovered.Broadcast(true);
			}
		}
	}
}