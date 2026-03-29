// Fill out your copyright notice in the Description page of Project Settings.


#include "TsushimaGrassSubsystem.h"
#include "SceneViewExtension.h"
#include "TsushimaSceneView.h"

void UTsushimaGrassSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	SceneView = FSceneViewExtensions::NewExtension<FTsushimaSceneView>();
}

void UTsushimaGrassSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UTsushimaGrassSubsystem::SetGrassContext(UTsushimaRenderSetting* InGrassSpec)
{
	if (SceneView)
	{
		SceneView->SetGrassData(GetWorld(), InGrassSpec);
	}
}
