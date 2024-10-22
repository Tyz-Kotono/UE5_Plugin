// Fill out your copyright notice in the Description page of Project Settings.


#include "CSBlurSubsystem.h"
#include "FCSBlurSceneViewExtension.h"
#include "SceneViewExtension.h"




void UCSBlurSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CustomSceneViewExtension = FSceneViewExtensions::NewExtension<FCSBlurSceneViewExtension>();
}

void UCSBlurSubsystem::Deinitialize()
{
	Super::Deinitialize();
	
	CustomSceneViewExtension.Reset();
	CustomSceneViewExtension = nullptr;
	
}
