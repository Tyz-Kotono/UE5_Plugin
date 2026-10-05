// Fill out your copyright notice in the Description page of Project Settings.


#include "LRayTracingSceneViewExtension.h"
#include "Misc/EngineVersionComparison.h"
#include "RayTracingShaderBindingLayout.h"
#include "RendererUtils.h"
#include "../Shader/LRayTracingShader.h"

#include "RenderGraphEvent.h"
#include "SceneRendering.h"
#include "ScenePrivate.h"
#include "PixelShaderUtils.h"
#include "RenderTargetPool.h"
#include "SceneRenderTargetParameters.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Runtime/Renderer/Internal/PostProcess/PostProcessInputs.h"
#include "Runtime/Renderer/Private/SceneRendering.h"

FLRayTracingSceneViewExtension::FLRayTracingSceneViewExtension(const FAutoRegister& AutoRegister) :
	FSceneViewExtensionBase(AutoRegister)
{
}

FLRayTracingSceneViewExtension::~FLRayTracingSceneViewExtension()
{
}

void FLRayTracingSceneViewExtension::SetupViewFamily(FSceneViewFamily& InViewFamily)
{
	FSceneViewExtensionBase::SetupViewFamily(InViewFamily);
}

void FLRayTracingSceneViewExtension::SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView)
{
	FSceneViewExtensionBase::SetupView(InViewFamily, InView);
}

void FLRayTracingSceneViewExtension::BeginRenderViewFamily(FSceneViewFamily& InViewFamily)
{
	FSceneViewExtensionBase::BeginRenderViewFamily(InViewFamily);
}

void FLRayTracingSceneViewExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View,
                                                                     const FPostProcessingInputs& Inputs)
{
	FSceneViewExtensionBase::PrePostProcessPass_RenderThread(GraphBuilder, View, Inputs);

#if RHI_RAYTRACING
	if (!View.bIsViewInfo || !View.bAllowRayTracing ||
		!View.Family || !View.Family->Scene)
	{
		return;
	}
	RayTracing(GraphBuilder, View, Inputs);

#endif
}

bool FLRayTracingSceneViewExtension::IsHardwareRayTracingAvailable(const FViewInfo& ViewInfo, const FScene* Scene) const
{
	if (!ViewInfo.InlineRayTracingBindingDataBuffer)
	{
		return false;
	}
#if UE_VERSION_NEWER_THAN_OR_EQUAL(5,8,0)
	if (!Scene || !Scene->RayTracingScene.GetRHIRayTracingScene(ERayTracingSceneLayer::Base,
	                                                            ViewInfo.GetRayTracingSceneViewHandle()))
	{
		return false;
	}
	return true;
#else
	return false;
#endif
}

DECLARE_GPU_DRAWCALL_STAT(LRayTracingRGS);

void FLRayTracingSceneViewExtension::RayTracing(FRDGBuilder& GraphBuilder, const FSceneView& View,
                                                const FPostProcessingInputs& Inputs)
{
	RDG_EVENT_SCOPE_STAT(GraphBuilder, LRayTracingRGS, "LRayTracingRGS");

#if RHI_RAYTRACING

	checkSlow(View.bIsViewInfo);
	const FViewInfo& ViewInfo = static_cast<const FViewInfo&>(View);
	const FScene* Scene = View.Family->Scene->GetRenderScene();

	if (!IsHardwareRayTracingAvailable(ViewInfo, Scene))
	{
		return;
	}


	const FIntRect ViewRect = static_cast<const FViewInfo&>(View).ViewRect;
	const FIntPoint OutputSize = ViewRect.Size();
	FGlobalShaderMap* ShaderMap = ViewInfo.ShaderMap;

	FRayTracingPipelineStateInitializer PipelineInitializer;

	auto RayGenShader = ShaderMap->GetShader<FLRayTracingRGS>();
	auto ClosestHitShader = ShaderMap->GetShader<FLRayTracingCHS>();
	auto MissShader = ShaderMap->GetShader<FLRayTracingMS>();


	const FShaderBindingLayout* ShaderBindingLayout = RayTracing::GetShaderBindingLayout(ViewInfo.GetShaderPlatform());
	if (ShaderBindingLayout)
	{
		PipelineInitializer.ShaderBindingLayout = &ShaderBindingLayout->RHILayout;
	}

	FRHIRayTracingShader* RayGenShaderTable[] = {RayGenShader.GetRayTracingShader()};
	FRHIRayTracingShader* HitGroupTable[] = {ClosestHitShader.GetRayTracingShader()};
	FRHIRayTracingShader* MissTable[] = {MissShader.GetRayTracingShader()};
	PipelineInitializer.SetRayGenShaderTable(MakeArrayView(RayGenShaderTable));
	PipelineInitializer.SetHitGroupTable(MakeArrayView(HitGroupTable));
	PipelineInitializer.SetMissShaderTable(MakeArrayView(MissTable));

	FRayTracingPipelineState* Pipeline = PipelineStateCache::GetAndOrCreateRayTracingPipelineState(
		GraphBuilder.RHICmdList, PipelineInitializer);

	FShaderBindingTableRHIRef SBT =
		Scene->RayTracingSBT.AllocateTransientRHI(
			GraphBuilder.RHICmdList,
			ERayTracingShaderBindingMode::RTPSO,
			ERayTracingHitGroupIndexingMode::Disallow,
			PipelineInitializer.GetMaxLocalBindingDataSize());

	const FRDGTextureDesc OutputDesc = FRDGTextureDesc::Create2D(
		OutputSize,
		PF_FloatRGBA,
		FClearValueBinding::Black,
		TexCreate_ShaderResource | TexCreate_UAV);
	FRDGTextureRef OutputTexture = GraphBuilder.CreateTexture(
		OutputDesc, TEXT("LRayTracing.Output"));

	FLRayTracingRGS::FParameters* RayGenParameters = GraphBuilder.AllocParameters<FLRayTracingRGS::FParameters>();
	RayGenParameters->TLAS = ViewInfo.GetRayTracingSceneLayerViewChecked(ERayTracingSceneLayer::Base);
	RayGenParameters->View = ViewInfo.ViewUniformBuffer;
	RayGenParameters->RWOutputTexture = GraphBuilder.CreateUAV(OutputTexture);
	RayGenParameters->Scene = ViewInfo.GetSceneUniforms().GetBuffer(GraphBuilder);
	RayGenParameters->NaniteRayTracing = Nanite::GetPublicGlobalRayTracingUniformBuffer();

	GraphBuilder.AddPass(
		RDG_EVENT_NAME("L RayTracing RDG"),
		RayGenParameters,
		ERDGPassFlags::Compute,
		[RayGenParameters, RayGenShader, &ViewInfo, SBT, Pipeline, ViewRect](
		FRDGAsyncTask, FRHICommandList& RHICmdList)
		{
			FRHIBatchedShaderParameters& ShaderParameters = RHICmdList.GetScratchShaderParameters();
			SetShaderParameters(ShaderParameters, RayGenShader, *RayGenParameters);

			FRHIUniformBuffer* SceneUniformBuffer = RayGenParameters->Scene->GetRHI();
			FRHIUniformBuffer* NaniteRayTracingUniformBuffer = RayGenParameters->NaniteRayTracing->GetRHI();
			TOptional<FScopedUniformBufferStaticBindings> StaticUniformBufferScope =
				RayTracing::BindStaticUniformBufferBindings(
					ViewInfo,
					SceneUniformBuffer,
					NaniteRayTracingUniformBuffer,
					RHICmdList);


			RHICmdList.SetDefaultRayTracingHitGroup(SBT, Pipeline, 0);
			RHICmdList.SetRayTracingMissShader(SBT, 0, Pipeline, 0, 0, nullptr, 0);
			RHICmdList.CommitShaderBindingTable(SBT);
			RHICmdList.RayTraceDispatch(Pipeline, RayGenShader.GetRayTracingShader(), SBT, ShaderParameters,
			                            ViewRect.Size().X, ViewRect.Size().Y);
		}

	);
#endif
}
