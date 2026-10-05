// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "LRayTracingSubSystem.generated.h"

class FSceneViewExtensionBase;
/**
 * 
 */
UCLASS()
class LRAYTRACING_API ULRayTracingSubSystem : public UWorldSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	TSharedPtr<FSceneViewExtensionBase, ESPMode::ThreadSafe> LRTSceneView ;
};
