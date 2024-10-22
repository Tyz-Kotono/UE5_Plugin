// Fill out your copyright notice in the Description page of Project Settings.


#include "LearnShaderSubsystem.h"
#include "LearnShaderSceneViewExtension.h"


void ULearnShaderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	// CustomSceneViewExtension = FSceneViewExtensions::NewExtension<LearnShaderSceneViewExtension>();
}

void ULearnShaderSubsystem::Deinitialize()
{
	Super::Deinitialize();
	CustomSceneViewExtension.Reset();
	CustomSceneViewExtension = nullptr;
}
