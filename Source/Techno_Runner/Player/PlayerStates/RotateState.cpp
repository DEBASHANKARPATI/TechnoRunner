// Fill out your copyright notice in the Description page of Project Settings.


#include "RotateState.h"
#include <GameFramework/Character.h>
#include <Kismet/KismetMathLibrary.h>

void ARotateState::Initialize(const float Degree )
{
	DegreeToRotate = Degree;
}

void ARotateState::Execute(ACharacter* const TargetCharacter)
{

	if (TargetCharacterRotation == FRotator::ZeroRotator)
	{
		TargetCharacterRotation.Yaw += DegreeToRotate;
	}

	FRotator ResultRotation = UKismetMathLibrary::RLerp(TargetCharacter->GetActorRotation(), TargetCharacterRotation ,GetWorld()->DeltaTimeSeconds,true);
	TargetCharacter->SetActorRotation(ResultRotation);

}
