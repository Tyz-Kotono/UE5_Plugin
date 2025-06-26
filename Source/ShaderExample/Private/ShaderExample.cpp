#include "ShaderExample.h"

#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FShaderExampleModule"

void FShaderExampleModule::StartupModule()
{
	const FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("TAShader"))->GetBaseDir(), TEXT("Shaders"));
	if(!AllShaderSourceDirectoryMappings().Contains(TEXT("/TAShader")))
	{
		AddShaderSourceDirectoryMapping(TEXT("/TAShader"), PluginShaderDir);
	}
}

void FShaderExampleModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FShaderExampleModule, ShaderExample)