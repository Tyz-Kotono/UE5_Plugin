// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuiltInRayTracingShaders.h"
#include "RayTracingShaderBindingLayout.h"
#include "RayTracingPayloadType.h"
#include "SceneUniformBuffer.h"
#include "Nanite/NaniteShared.h"
#include "ShaderParameterStruct.h"


//Shader Property Struct
BEGIN_SHADER_PARAMETER_STRUCT(FLRayTracingRGSParams,)
	SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, View)
	SHADER_PARAMETER_RDG_UNIFORM_BUFFER(FSceneUniformParameters, Scene)
	SHADER_PARAMETER_RDG_UNIFORM_BUFFER(FNaniteRayTracingUniformParameters, NaniteRayTracing)

	SHADER_PARAMETER_RDG_BUFFER_SRV(RaytracingAccelerationStructure, TLAS)
	SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4>, RWOutputTexture)


END_SHADER_PARAMETER_STRUCT()

class FLRayTracingRGS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FLRayTracingRGS)
	using FParameters = FLRayTracingRGSParams;
	SHADER_USE_ROOT_PARAMETER_STRUCT(FLRayTracingRGS, FGlobalShader)

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return ShouldCompileRayTracingShadersForProject(Parameters.Platform);
	}

	static ERayTracingPayloadType GetRayTracingPayloadType(const int32 PermutationId)
	{
		return ERayTracingPayloadType::Default;
	}

	static const FShaderBindingLayout* GetShaderBindingLayout(const FShaderPermutationParameters& Parameters)
	{
		return RayTracing::GetShaderBindingLayout(Parameters.Platform);
	}
};

class FLRayTracingCHS : public FGlobalShader
{
public:
	DECLARE_GLOBAL_SHADER(FLRayTracingCHS)
	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters,
	                                         FShaderCompilerEnvironment& OutEnvironment)
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
	}

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return ShouldCompileRayTracingShadersForProject(Parameters.Platform);
	}

	static ERayTracingPayloadType GetRayTracingPayloadType(const int32 PermutationId)
	{
		return ERayTracingPayloadType::Default;
	}

	static const FShaderBindingLayout* GetShaderBindingLayout(const FShaderPermutationParameters& Parameters)
	{
		return RayTracing::GetShaderBindingLayout(Parameters.Platform);
	}
};

class FLRayTracingMS : public FBuiltInRayTracingShader
{
public:
	DECLARE_EXPORTED_SHADER_TYPE(FLRayTracingMS, Global,);

	static ERayTracingPayloadType GetRayTracingPayloadType(const int32 PermutationId)
	{
		return ERayTracingPayloadType::Default;
	}

	FLRayTracingMS() = default;

	FLRayTracingMS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FBuiltInRayTracingShader(Initializer)
	{
	}
};
