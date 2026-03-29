// Copyright Epic Games, Inc. All Rights Reserved.

#include "TsushimaGrass.h"

#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FTsushimaGrassModule"

void FTsushimaGrassModule::StartupModule()
{
	const FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("TsushimaGrass"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/TsushimaGrass"), PluginShaderDir);
}

void FTsushimaGrassModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTsushimaGrassModule, TsushimaGrass)