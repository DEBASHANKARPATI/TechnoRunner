// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"
/**
 * Resposible for controlling player inputs 
 */
UCLASS()
class TECHNO_RUNNER_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	void Tick(float DeltaTime) override;
	void BeginPlay() override;
	
};
