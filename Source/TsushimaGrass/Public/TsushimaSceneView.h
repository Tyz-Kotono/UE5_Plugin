// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SceneViewExtension.h"

class UTsushimaRenderSetting;

class TSUSHIMAGRASS_API FTsushimaSceneView : public FSceneViewExtensionBase
{
public:
	FTsushimaSceneView(const FAutoRegister& AutoRegister);
	virtual ~FTsushimaSceneView() override;
	virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override;
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;
	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;
	virtual void PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView);
	virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View,
	                                             const FPostProcessingInputs& Inputs) override;

	static void BaseGlobalShader_RenderThread(
		FRDGBuilder& GraphBuilder,
		const FSceneView& View,
		const FPostProcessingInputs& Inputs,
		FIntRect Viewport,
		const FGlobalShaderMap* GlobalShaderMap,
		UTsushimaRenderSetting* GrassSpec);


	void SetGrassData(UWorld* InWorld, UTsushimaRenderSetting* InGrassSpec);

private:
	UPROPERTY(BlueprintAssignable)
	TObjectPtr<UWorld> World;
	UPROPERTY(BlueprintAssignable)
	TObjectPtr<UTsushimaRenderSetting> GrassSpec;
	UPROPERTY(BlueprintAssignable)
	TRefCountPtr<IPooledRenderTarget> PooledPersistentRT;

	int32 CacheResolution;
};
