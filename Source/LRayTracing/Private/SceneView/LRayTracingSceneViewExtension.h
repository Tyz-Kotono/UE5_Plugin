// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SceneViewExtension.h"


class LRAYTRACING_API FLRayTracingSceneViewExtension : public FSceneViewExtensionBase
{
public:
	FLRayTracingSceneViewExtension(const FAutoRegister& AutoRegister);
	virtual ~FLRayTracingSceneViewExtension() override;
	virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override;
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;
	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;
	
	virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View,
												 const FPostProcessingInputs& Inputs) override;
	bool IsHardwareRayTracingAvailable(const FViewInfo& ViewInfo, const FScene* Scene) const;
	void RayTracing(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs);
};
