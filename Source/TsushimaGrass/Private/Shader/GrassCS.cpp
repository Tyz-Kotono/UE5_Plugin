// Fill out your copyright notice in the Description page of Project Settings.


#include "Shader/GrassCS.h"
#include "PixelShaderUtils.h"
#include "RenderGraphEvent.h"
#include "RenderGraphUtils.h"
#include "ShaderParameterStruct.h"
#include "SystemTextures.h"
#include "TsushimaRenderSetting.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Runtime/Renderer/Private/SceneRendering.h"


class FTsushimaGrassCS : public FGlobalShader
{
	DECLARE_EXPORTED_SHADER_TYPE(FTsushimaGrassCS, Global, TSUSHIMAGRASS_API);

	SHADER_USE_PARAMETER_STRUCT(FTsushimaGrassCS, FGlobalShader)
	BEGIN_SHADER_PARAMETER_STRUCT(FParameters,)
		SHADER_PARAMETER(uint32, Resolution)
		//R MidPoint G Curve B Center Width A Button Width
		SHADER_PARAMETER(FVector4f, GrassShape)
		SHADER_PARAMETER(FVector4f, MidribRimData)
		SHADER_PARAMETER(uint32, bHasPrevious)
		SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float>, PreviousTexture)
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4>, GrassPositionTexture2D)
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4>, GrassNormalTexture2D)
	END_SHADER_PARAMETER_STRUCT()

public:
	static constexpr uint32 NumThreadsX = 16;
	static constexpr uint32 NumThreadsY = 16;

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
	FRDGTextureRef OutputPositionTexture,
	FRDGTextureRef OutputNormalTexture)
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
	Parameters->GrassShape = FVector4f(
		GrassSpec->MinPoint,
		GrassSpec->GrassCurve,
		GrassSpec->CenterWidth,
		GrassSpec->ButtonWidth
	);

	Parameters->MidribRimData = FVector4f(
		GrassSpec->RimPosition,
		GrassSpec->RimSoftness,
		GrassSpec->MidribSoftness,
		GrassSpec->RimIntensity
	);
	Parameters->Resolution = Resolution;
	Parameters->bHasPrevious = bHasPrevious ? 1 : 0;
	Parameters->GrassPositionTexture2D = GraphBuilder.CreateUAV(OutputPositionTexture);
	Parameters->GrassNormalTexture2D = GraphBuilder.CreateUAV(OutputNormalTexture);

	const FIntVector GroupCount(
		FMath::DivideAndRoundUp(Resolution, FTsushimaGrassCS::NumThreadsX),
		FMath::DivideAndRoundUp(Resolution, FTsushimaGrassCS::NumThreadsY),
		1
	);

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
	if (!GrassSpec->GrassPositionRT.IsValid() || !GrassSpec->GrassNormalRT.IsValid())
	{
		return;
	}

	auto GrassPositionRT = GrassSpec->GrassPositionRT.Get();
	auto GrassNormalRT = GrassSpec->GrassNormalRT.Get();


	FTextureRenderTargetResource* PositionRTResource = GrassPositionRT->GetRenderTargetResource();
	FTextureRenderTargetResource* NormalRTResource = GrassNormalRT->GetRenderTargetResource();
	if (!PositionRTResource)
	{
		return;
	}

	// === 外部 RT ===
	FRHITexture* TextureRHI = PositionRTResource->GetRenderTargetTexture();

	FRDGTextureRef RDGPositionTexture = GraphBuilder.RegisterExternalTexture(
		CreateRenderTarget(PositionRTResource->GetRenderTargetTexture(), TEXT("GrassPositionRT"))
	);

	FRDGTextureRef RDGNormalTexture = GraphBuilder.RegisterExternalTexture(
		CreateRenderTarget(NormalRTResource->GetRenderTargetTexture(), TEXT("GrassNormalRT"))
	);

	const int32 Resolution = GrassPositionRT->SizeX;
	//TODO
	//|| GrassPositionRT->SizeY != Resolution
	if (Resolution <= 0 || GrassPositionRT->GetFormat() != PF_FloatRGBA)
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
		FIntPoint(Resolution, Resolution),
		PF_FloatRGBA,
		FClearValueBinding::Black,
		TexCreate_ShaderResource | TexCreate_UAV
	);

	FRDGTextureRef RDGOutputPosition = GraphBuilder.CreateTexture(OutputDesc, TEXT("GrassPositionOutput"));
	FRDGTextureRef RDGOutputNormal = GraphBuilder.CreateTexture(OutputDesc, TEXT("GrassNormalOutput"));

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
		RDGOutputPosition,
		RDGOutputNormal // ✅ 新增
	);

	// === Copy 到目标 RT ===
	AddCopyTexturePass(GraphBuilder, RDGOutputPosition, RDGPositionTexture);
	AddCopyTexturePass(GraphBuilder, RDGOutputNormal, RDGNormalTexture);

	// === 提取为下一帧历史 ===
	GraphBuilder.QueueTextureExtraction(RDGOutputPosition, &PooledPersistentRT);
}

void FTsushimaGrassInterface::ResetPersistentResources(TRefCountPtr<IPooledRenderTarget>& PooledPersistentRT)
{
	if (PooledPersistentRT.IsValid())
	{
		PooledPersistentRT = nullptr;
	}
}
