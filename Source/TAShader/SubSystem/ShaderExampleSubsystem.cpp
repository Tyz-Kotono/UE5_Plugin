// Fill out your copyright notice in the Description page of Project Settings.


#include "ShaderExampleSubsystem.h"

#include "ShaderExampleDataAsset.h"
#include "ShaderExampleSceneViewExtension.h"

void UShaderExampleSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ExampleSceneViewExtension = FSceneViewExtensions::NewExtension<FShaderExampleSceneViewExtension>();
}

void UShaderExampleSubsystem::Deinitialize()
{
	Super::Deinitialize();

}

void UShaderExampleSubsystem::AddExampleData(UShaderExampleDataAsset* Data)
{
	ExampleData = Data;
	ExampleSceneViewExtension ->SetExampleData(ExampleData);
}
