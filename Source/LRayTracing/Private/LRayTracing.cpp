// Copyright Epic Games, Inc. All Rights Reserved.

#include "LRayTracing.h"

#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FLRayTracingModule"

void FLRayTracingModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	const FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("LRayTracing"))->GetBaseDir(), TEXT("Shaders"));
	if(!AllShaderSourceDirectoryMappings().Contains(TEXT("/LRayTracing")))
	{
		AddShaderSourceDirectoryMapping(TEXT("/LRayTracing"), PluginShaderDir);
	}
}

void FLRayTracingModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLRayTracingModule, LRayTracing)