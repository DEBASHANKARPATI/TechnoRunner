// Fill out your copyright notice in the Description page of Project Settings.


#include "TechnoRunnerGameInstance.h"
#include <Techno_Runner/Core/Optimization/Pool.h>
#include <Techno_Runner/Level/LevelEditor.h>

APool* UTechnoRunnerGameInstance::GetPool() const
{
	return ObjectPool;
}

ALevelEditor* UTechnoRunnerGameInstance::GetLevelEditor() const
{
	return LevelEditor;
}

void UTechnoRunnerGameInstance::Init()
{
	Super::Init();

	if (const auto World = GetWorld())
	{
		ObjectPool = World->SpawnActor<APool>(ObjectPoolAsset);
		LevelEditor = World->SpawnActor<ALevelEditor>(LevelEditorAsset);
	}
}
