#pragma once
#include "SceneViewExtension.h"

class LEARNSHADER_API RenderTargetSceneViewExtension:public FSceneViewExtensionBase
{
private:
	TObjectPtr<UTextureRenderTarget2D> RenderTargetSource = nullptr;
	//渲染目标引用计数
	TRefCountPtr<IPooledRenderTarget> PooledRenderTarget;
	
public:
	RenderTargetSceneViewExtension(const FAutoRegister& AutoRegister);
	virtual ~RenderTargetSceneViewExtension() override;
	virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override;
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;
	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;

	virtual void PostRenderBasePassDeferred_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView, const FRenderTargetBindingSlots& RenderTargets, TRDGUniformBufferRef<FSceneTextureUniformParameters> SceneTextures) override {};
	virtual void PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override {};
	virtual void PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override {};
	virtual void PostRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override {};
	virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs) override;
	virtual void PostRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override {};

	void SetRenderTarget(UTextureRenderTarget2D* RenderTarget);
private:
	//默认要求_RenderThread
	void CreatePooledRenderTarget_RenderThread();
};
