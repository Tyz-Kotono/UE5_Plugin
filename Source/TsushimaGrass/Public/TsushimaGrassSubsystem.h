// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TsushimaGrassSubsystem.generated.h"


class UTsushimaRenderSetting;
class FTsushimaSceneView;



UCLASS()
class TSUSHIMAGRASS_API UTsushimaGrassSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
private:
	TSharedPtr<FTsushimaSceneView, ESPMode::ThreadSafe> SceneView;
	UFUNCTION(BlueprintCallable)
	void SetGrassContext(UTsushimaRenderSetting* Data);
};
