// Copyright Epic Games, Inc. All Rights Reserved.

#include "LearnShader.h"

#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FLearnShaderModule"

void FLearnShaderModule::StartupModule()
{
	const FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("LearnShader"))->GetBaseDir(), TEXT("Shaders"));
	if(!AllShaderSourceDirectoryMappings().Contains(TEXT("/LearnShader")))
	{
		AddShaderSourceDirectoryMapping(TEXT("/LearnShader"), PluginShaderDir);
	}
}

void FLearnShaderModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLearnShaderModule, LearnShader)