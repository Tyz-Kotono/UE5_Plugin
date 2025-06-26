// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "ShaderExampleSubsystem.generated.h"

class UShaderExampleDataAsset;
class FShaderExampleSceneViewExtension;
class FSceneViewExtensionBase;




UCLASS()
class TASHADER_API UShaderExampleSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
private:
	TSharedPtr<FShaderExampleSceneViewExtension, ESPMode::ThreadSafe> ExampleSceneViewExtension;
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;


public:
	UPROPERTY(BlueprintReadWrite, Category="ShaderExample")
	TObjectPtr<UShaderExampleDataAsset> ExampleData;
	UFUNCTION(BlueprintCallable, Category="ShaderExample")
	void AddExampleData(UShaderExampleDataAsset* Data);
};
