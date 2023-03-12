// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TechnoRunnerGameInstance.generated.h"
class ALevelEditor;
class APool;
/**
 * Responsible for creating objects for global and single access 
 */
UCLASS()
class TECHNO_RUNNER_API UTechnoRunnerGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	APool* GetPool() const;
	ALevelEditor* GetLevelEditor() const;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APool> ObjectPoolAsset;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ALevelEditor> LevelEditorAsset;

	void Init() override;

private:
	APool* ObjectPool;
	ALevelEditor* LevelEditor;

};
