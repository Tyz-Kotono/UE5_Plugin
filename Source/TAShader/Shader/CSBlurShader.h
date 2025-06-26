#pragma once
#include "CoreMinimal.h"
#include "DataDrivenShaderPlatformInfo.h"
#include "PostProcess/PostProcessInputs.h"

BEGIN_SHADER_PARAMETER_STRUCT(FCSBlurParams,)
	SHADER_PARAMETER_SAMPLER(SamplerState, SceneColorSampler)
	SHADER_PARAMETER_RDG_TEXTURE(Texture2D, SceneColorTexture)
	SHADER_PARAMETER_RDG_TEXTURE_UAV(Texture2D, OutputTexture)
END_SHADER_PARAMETER_STRUCT()

class FCSBlurShader: public FGlobalShader
{
	DECLARE_EXPORTED_SHADER_TYPE(FCSBlurShader, Global, );
	using FParameters = FCSBlurParams;
	SHADER_USE_PARAMETER_STRUCT(FCSBlurShader, FGlobalShader);

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}
	
	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
		OutEnvironment.CompilerFlags.Add(CFLAG_AllowTypedUAVLoads);
	}
};
