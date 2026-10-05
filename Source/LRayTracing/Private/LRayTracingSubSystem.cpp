// Fill out your copyright notice in the Description page of Project Settings.


#include "LRayTracingSubSystem.h"

#include "SceneViewExtension.h"
#include "SceneView/LRayTracingSceneViewExtension.h"


void ULRayTracingSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	LRTSceneView = FSceneViewExtensions::NewExtension<FLRayTracingSceneViewExtension>();
}

void ULRayTracingSubSystem::Deinitialize()
{
	Super::Deinitialize();
	if (LRTSceneView.IsValid())
	{
		LRTSceneView.Reset();
		LRTSceneView = nullptr;
	}
}
TStatId ULRayTracingSubSystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(ULRayTracingSubSystem, STATGROUP_Tickables);
}

void ULRayTracingSubSystem::Tick(float DeltaTime)
{
}


