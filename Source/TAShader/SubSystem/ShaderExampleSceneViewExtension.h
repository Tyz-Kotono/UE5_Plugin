#pragma once
#include "SceneViewExtension.h"

class UShaderExampleDataAsset;

class TASHADER_API FShaderExampleSceneViewExtension:public FSceneViewExtensionBase
{
public:
	FShaderExampleSceneViewExtension(const FAutoRegister& AutoRegister);
	virtual ~FShaderExampleSceneViewExtension() override;
	virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override;
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;
	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;

	virtual void PostRenderBasePassDeferred_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView, const FRenderTargetBindingSlots& RenderTargets, TRDGUniformBufferRef<FSceneTextureUniformParameters> SceneTextures) override {};
	virtual void PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override {};
	virtual void PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override {};
	virtual void PostRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override {};
	virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs) override;
	virtual void PostRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override {};


	//Base Data
	TObjectPtr<UShaderExampleDataAsset> ExampleData;
	void SetExampleData(UShaderExampleDataAsset* Data);

	//Render
	void BaseGlobalShader_RenderThread(FRDGBuilder& GraphBuilder,
	const FSceneView& View, const FPostProcessingInputs& Inputs,FIntRect Viewport,const FGlobalShaderMap* GlobalShaderMap);

	//RenderTarget
	TRefCountPtr<IPooledRenderTarget> PooledRenderTarget;
	void RenderTarget_RenderThread(FRDGBuilder& GraphBuilder,
	const FSceneView& View, const FPostProcessingInputs& Inputs,FIntRect Viewport,const FGlobalShaderMap* GlobalShaderMap);
private:
	
	void CreatePooledRenderTarget_RenderThread();

	
public:
	void ComputerShaderBlur_RenderThread(FRDGBuilder& GraphBuilder,
	const FSceneView& View, const FPostProcessingInputs& Inputs,FIntRect Viewport,const FGlobalShaderMap* GlobalShaderMap);
};
