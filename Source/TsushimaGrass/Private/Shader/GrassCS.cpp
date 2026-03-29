// Fill out your copyright notice in the Description page of Project Settings.


#include "Shader/GrassCS.h"

#include "BaseShaderPS.h"
#include "PixelShaderUtils.h"
#include "RenderGraphEvent.h"
#include "RenderGraphUtils.h"
#include "RenderTargetPool.h"
#include "ShaderParameterStruct.h"
#include "SystemTextures.h"
#include "TsushimaRenderSetting.h"
#include "Engine/TextureRenderTarget2D.h"
#include "PostProcess/PostProcessInputs.h"
#include "Runtime/Renderer/Private/SceneRendering.h"
#include "SceneRenderTargetParameters.h"


class FTsushimaGrassCS : public FGlobalShader
{
	DECLARE_EXPORTED_SHADER_TYPE(FTsushimaGrassCS, Global, TSUSHIMAGRASS_API);

	SHADER_USE_PARAMETER_STRUCT(FTsushimaGrassCS, FGlobalShader)
	BEGIN_SHADER_PARAMETER_STRUCT(FParameters,)
		SHADER_PARAMETER(uint32, Resolution)
		//R MidPoint G Curve B Center Width A Button Width
		SHADER_PARAMETER(FVector4f, MCWW)
		SHADER_PARAMETER(uint32, bHasPrevious)
		SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float>, PreviousTexture)
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4>, OutTexture2D)
	END_SHADER_PARAMETER_STRUCT()

public:
	static constexpr uint32 NumThreadsX = 2;
	static constexpr uint32 NumThreadsY = 8;

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters,
	                                         FShaderCompilerEnvironment& OutEnvironment)
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
		OutEnvironment.SetDefine("NUM_THREADS_X", NumThreadsX);
		OutEnvironment.SetDefine("NUM_THREADS_Y", NumThreadsY);
	}
};

IMPLEMENT_GLOBAL_SHADER(FTsushimaGrassCS, "/TsushimaGrass/Private/TsushimaGrass.usf",
                        "TsushimaGrassMain",
                        SF_Compute);

void FTsushimaGrassInterface::Grass_RenderThread(
	FRDGBuilder& GraphBuilder,
	const FGlobalShaderMap* ShaderMap,
	uint32 Resolution,
	const UTsushimaRenderSetting* GrassSpec,
	FRDGTextureRef PreviousTexture,
	FRDGTextureRef OutputTextureRef)
{
	RDG_EVENT_SCOPE(GraphBuilder, "TsushimaGrass");

	TShaderMapRef<FTsushimaGrassCS> ComputeShader(ShaderMap);

	FTsushimaGrassCS::FParameters* Parameters =
		GraphBuilder.AllocParameters<FTsushimaGrassCS::FParameters>();

	const bool bHasPrevious = (PreviousTexture != nullptr);

	FRDGTextureRef SafePreviousTexture = bHasPrevious
		                                     ? PreviousTexture
		                                     : GraphBuilder.RegisterExternalTexture(GSystemTextures.BlackDummy);

	Parameters->PreviousTexture = GraphBuilder.CreateSRV(SafePreviousTexture);
	Parameters->MCWW = FVector4f(
		GrassSpec->MinPoint,
		GrassSpec->GrassCurve,
		GrassSpec->CenterWidth,
		GrassSpec->ButtonWidth
	);
	Parameters->Resolution = Resolution;
	Parameters->bHasPrevious = bHasPrevious ? 1 : 0;
	Parameters->OutTexture2D = GraphBuilder.CreateUAV(OutputTextureRef);

	const FIntVector GroupCount(
		FMath::DivideAndRoundUp(Resolution, FTsushimaGrassCS::NumThreadsX),
		FMath::DivideAndRoundUp(Resolution, FTsushimaGrassCS::NumThreadsY),
		1
	);
	// UE_LOG(LogTemp, Warning, TEXT(" Size: %d x %d"),
	//        OutputTextureRef->Desc.Extent.X,
	//        OutputTextureRef->Desc.Extent.Y
	// );
	// UE_LOG(LogTemp, Warning, TEXT("OutputTexture Format: %d"),
	//        (int32)OutputTextureRef->Desc.Format
	// );
	FComputeShaderUtils::AddPass(
		GraphBuilder,
		RDG_EVENT_NAME("TsushimaGrassCS"),
		ComputeShader,
		Parameters,
		FIntVector(1, 1, 1)
		// GroupCount
	);
}

void FTsushimaGrassInterface::AddPass_RenderThread(
	FRDGBuilder& GraphBuilder,
	const FSceneView& View,
	const FPostProcessingInputs& Inputs,
	UTsushimaRenderSetting* GrassSpec,
	TRefCountPtr<IPooledRenderTarget>& PooledPersistentRT,
	int32& CacheResolution)
{
	if (!GrassSpec->GrassRT.IsValid())
	{
		return;
	}

	auto RenderTarget = GrassSpec->GrassRT.Get();

	FTextureRenderTargetResource* RTResource = RenderTarget->GetRenderTargetResource();
	if (!RTResource)
	{
		return;
	}

	// === 外部 RT ===
	FRHITexture* TextureRHI = RTResource->GetRenderTargetTexture();

	FRDGTextureRef RDGTexture = GraphBuilder.RegisterExternalTexture(
		CreateRenderTarget(TextureRHI, TEXT("TsushimaGrassRT"))
	);

	const int32 Resolution = RenderTarget->SizeX;
	//TODO
	//|| RenderTarget->SizeY != Resolution
	if (Resolution <= 0  || RenderTarget->GetFormat() != PF_FloatRGBA)
	{
		return;
	}

	// 分辨率变化 → 重置历史
	if (CacheResolution != Resolution)
	{
		ResetPersistentResources(PooledPersistentRT);
		CacheResolution = Resolution;
	}
	

	const FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);

	//TODO
	// === 输出 RT ===  Resolution
	FRDGTextureDesc OutputDesc = FRDGTextureDesc::Create2D(
		FIntPoint(RenderTarget->SizeX, RenderTarget->SizeY),
		PF_FloatRGBA,
		FClearValueBinding::Black,
		TexCreate_ShaderResource | TexCreate_UAV
	);

	FRDGTextureRef RDGOutputTexture = GraphBuilder.CreateTexture(
		OutputDesc,
		TEXT("TsushimaGrassOutput")
	);

	// =========================
	// 历史帧处理
	// =========================
	FRDGTextureRef PreviousRDGTexture = nullptr;

	if (PooledPersistentRT.IsValid())
	{
		PreviousRDGTexture = GraphBuilder.RegisterExternalTexture(
			PooledPersistentRT,
			TEXT("TsushimaGrassPersistent")
		);
	}

	// === Compute Pass ===
	Grass_RenderThread(
		GraphBuilder,
		GlobalShaderMap,
		Resolution,
		GrassSpec,
		PreviousRDGTexture,
		RDGOutputTexture
	);

	// === Copy 到目标 RT ===
	AddCopyTexturePass(GraphBuilder, RDGOutputTexture, RDGTexture);

	// === 提取为下一帧历史 ===
	GraphBuilder.QueueTextureExtraction(RDGOutputTexture, &PooledPersistentRT);
}

void FTsushimaGrassInterface::ResetPersistentResources(TRefCountPtr<IPooledRenderTarget>& PooledPersistentRT)
{
	if (PooledPersistentRT.IsValid())
	{
		PooledPersistentRT = nullptr;
	}
}
