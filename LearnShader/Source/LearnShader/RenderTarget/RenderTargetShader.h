#pragma once

#include "CoreMinimal.h"
#include "DataDrivenShaderPlatformInfo.h"
#include "SceneTexturesConfig.h"
#include "PostProcess/PostProcessInputs.h"

BEGIN_SHADER_PARAMETER_STRUCT(FRenderTargetParams,)
	//定义颜色、贴图参数
	SHADER_PARAMETER(FVector3f, TargetColour)
	SHADER_PARAMETER(FVector2f, TextureSize)
	SHADER_PARAMETER_SAMPLER(SamplerState, SceneColorSampler)
	SHADER_PARAMETER_RDG_TEXTURE(Texture2D, SceneColorTexture)

	RENDER_TARGET_BINDING_SLOTS()
END_SHADER_PARAMETER_STRUCT()


class FRenderTargetPS : public FGlobalShader
{
	DECLARE_EXPORTED_SHADER_TYPE(FRenderTargetPS, Global, );
	using FParameters = FRenderTargetParams;
	SHADER_USE_PARAMETER_STRUCT(FRenderTargetPS, FGlobalShader);
};

class FRenderTargetNewPS : public FGlobalShader
{
	DECLARE_SHADER_TYPE(FRenderTargetNewPS, Global);
public:
	FRenderTargetNewPS() {}
	FRenderTargetNewPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FGlobalShader(Initializer)
	{
		FinalColor.Bind(Initializer.ParameterMap, TEXT("FinalColor"));
	}

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
	}
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}

	void SetParameters(FRHIBatchedShaderParameters& BatchedParameters, const FLinearColor& Color)
	{
		SetShaderValue(BatchedParameters, FinalColor, Color);
	}

private:
	LAYOUT_FIELD(FShaderParameter, FinalColor);
};


class FRenderTargetNewVS : public FGlobalShader
{
public:
	DECLARE_SHADER_TYPE(FRenderTargetNewVS, Global);


	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
		
		//SET_SHADER_DEFINE(OutEnvironment, YOUR_SHADER_MARCO, 0);
	}
	
};