// Fill out your copyright notice in the Description page of Project Settings.


#include "TsushimaSceneView.h"

#include "TsushimaRenderSetting.h"
#include "Shader/GrassCS.h"

#include "PixelShaderUtils.h"
#include "RenderTargetPool.h"
#include "SceneRenderTargetParameters.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Runtime/Renderer/Internal/PostProcess/PostProcessInputs.h"
#include "Runtime/Renderer/Private/SceneRendering.h"
#include "Shader/BaseShaderPS.h"

FTsushimaSceneView::FTsushimaSceneView(const FAutoRegister& AutoRegister) : FSceneViewExtensionBase(AutoRegister)
{
}

FTsushimaSceneView::~FTsushimaSceneView()
{
}

void FTsushimaSceneView::SetupViewFamily(FSceneViewFamily& InViewFamily)
{
	FSceneViewExtensionBase::SetupViewFamily(InViewFamily);
}

void FTsushimaSceneView::SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView)
{
	FSceneViewExtensionBase::SetupView(InViewFamily, InView);
}

void FTsushimaSceneView::BeginRenderViewFamily(FSceneViewFamily& InViewFamily)
{
	FSceneViewExtensionBase::BeginRenderViewFamily(InViewFamily);
}

void FTsushimaSceneView::PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView)
{
	FSceneViewExtensionBase::PreRenderView_RenderThread(GraphBuilder, InView);
	// if (IsValid(World) && GrassSpec)
	// {
	// 	FTsushimaGrassInterface::AddPass_RenderThread(
	// 		GraphBuilder,
	// 		InView,
	// 		World,
	// 		GrassSpec,
	// 		PooledPersistentRT,
	// 		CacheResolution);
	// }
}

void FTsushimaSceneView::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View,
                                                         const FPostProcessingInputs& Inputs)
{
	FSceneViewExtensionBase::PrePostProcessPass_RenderThread(GraphBuilder, View, Inputs);
	if (!GrassSpec)
	{
		return;
	}

	checkSlow(View.bIsViewInfo);
	const FIntRect Viewport = static_cast<const FViewInfo&>(View).ViewRect;
	const FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);

	if (GrassSpec->EnableBaseRender)
	{
		BaseGlobalShader_RenderThread(GraphBuilder, View, Inputs, Viewport, GlobalShaderMap, GrassSpec);
	}


	if (GrassSpec)
	{
		FTsushimaGrassInterface::AddPass_RenderThread(
			GraphBuilder,
			View,
			Inputs,
			GrassSpec,
			PooledPersistentRT,
			CacheResolution);
	}
}

void FTsushimaSceneView::BaseGlobalShader_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View,
                                                       const FPostProcessingInputs& Inputs, FIntRect Viewport,
                                                       const FGlobalShaderMap* GlobalShaderMap,
                                                       UTsushimaRenderSetting* GrassSpec)
{
	// UE_LOG(LogTemp, Warning, TEXT("这是一个调试信息！"));
	//Unreal Insights
	RDG_GPU_STAT_SCOPE(GraphBuilder, BasePass);
	// RenderDoc
	RDG_EVENT_SCOPE(GraphBuilder, "Base Pass");

	//抓取场景纹理
	const FSceneTextureShaderParameters SceneTextures = CreateSceneTextureShaderParameters(
		GraphBuilder, View, ESceneTextureSetupMode::SceneColor | ESceneTextureSetupMode::GBuffers);
	// 这是实际上带有阴影和阴影的颜色
	const FScreenPassTexture SceneColourTexture((*Inputs.SceneTextures)->SceneColorTexture, Viewport);

	FLinearColor Color = GrassSpec->ScreenColor;
	FVector3f ScreenColor = FVector3f(Color.R, Color.G, Color.B);

	//设置Global Shader 数据，分配内存
	FBaseShaderPS::FParameters* Parameters = GraphBuilder.AllocParameters<FBaseShaderPS::FParameters>();
	Parameters->SceneColorTexture = SceneColourTexture.Texture;
	Parameters->SceneTextures = SceneTextures;
	Parameters->TargetColour = ScreenColor;
	// Parameters->View = View.ViewUniformBuffer;

	//设置RenderTarget 和 Return Texture
	Parameters->RenderTargets[0] = FRenderTargetBinding((*Inputs.SceneTextures)->SceneColorTexture,
	                                                    ERenderTargetLoadAction::ELoad);

	TShaderMapRef<FBaseShaderPS> PixelShader(GlobalShaderMap);


	FPixelShaderUtils::AddFullscreenPass(GraphBuilder, GlobalShaderMap, FRDGEventName(TEXT("Base Pass")), PixelShader,
	                                     Parameters, Viewport);
}

void FTsushimaSceneView::SetGrassData(UWorld* InWorld, UTsushimaRenderSetting* InGrassSpec)
{
	GrassSpec = InGrassSpec;
	World = InWorld;
}
