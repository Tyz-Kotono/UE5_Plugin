// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SceneViewExtension.h"
#include "Subsystems/EngineSubsystem.h"
#include "CSBlurSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class LEARNSHADER_API UCSBlurSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
private:
	TSharedPtr<FSceneViewExtensionBase, ESPMode::ThreadSafe> CustomSceneViewExtension;

	// The source render target texture asset
	UPROPERTY()
	TObjectPtr<UTextureRenderTarget2D> RenderTargetSource = nullptr;
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};
