// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "LearnShaderSubsystem.generated.h"

class FSceneViewExtensionBase;

UCLASS()
class LEARNSHADER_API ULearnShaderSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

private:
	TSharedPtr<FSceneViewExtensionBase, ESPMode::ThreadSafe> CustomSceneViewExtension;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	//被移除时执行
	virtual void Deinitialize() override;
};
