// Fill out your copyright notice in the Description page of Project Settings.


#include "StrafeState.h"
#include <Kismet/KismetMathLibrary.h>
#include <GameFramework/Character.h>
void AStrafeState::Initialize(const FVector& InStrafeLocation)
{
	StrafeLocation = InStrafeLocation;
}

void AStrafeState::Execute(ACharacter* const Characater)
{
	FVector ResultFevctor = UKismetMathLibrary::VLerp(Characater->GetActorLocation(), StrafeLocation, GetWorld()->GetDeltaSeconds()*5);
	Characater->SetActorLocation(ResultFevctor);
}
