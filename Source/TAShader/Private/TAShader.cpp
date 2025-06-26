// Copyright Epic Games, Inc. All Rights Reserved.

#include "TAShader.h"

#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FTAShaderModule"

void FTAShaderModule::StartupModule()
{
	const FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("TAShader"))->GetBaseDir(), TEXT("Shaders"));
	if(!AllShaderSourceDirectoryMappings().Contains(TEXT("/TAShader")))
	{
		AddShaderSourceDirectoryMapping(TEXT("/TAShader"), PluginShaderDir);
	}
}

void FTAShaderModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTAShaderModule, TAShader)