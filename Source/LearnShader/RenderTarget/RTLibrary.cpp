// Fill out your copyright notice in the Description page of Project Settings.


#include "RTLibrary.h"

#include "RenderTargetShader.h"
#include "TextureResource.h"
#include "Engine/TextureRenderTarget2D.h"
#include "PixelShaderUtils.h"
#include "RenderGraphBuilder.h"
#include "RenderTargetPool.h"
#include "UniversalObjectLocatorResolveParams.h"
#include "TextureResource.h"
#include "Engine/TextureRenderTarget2D.h"


class FRenderTargetPS;

void URTLibrary::DrawRenderTarget_Function(UTextureRenderTarget2D* OutRenderTarget, const FLinearColor Color,
                                           const UObject* WorldActor)
{
	check(IsInGameThread());

	if (!OutRenderTarget)
	{
		return;
	}
	FTextureRenderTargetResource* TextureRenderTargetResource = OutRenderTarget->GameThread_GetRenderTargetResource();
	ERHIFeatureLevel::Type FeatureLevel = WorldActor->GetWorld()->Scene->GetFeatureLevel();

	if (FeatureLevel < ERHIFeatureLevel::SM5)
	{
		return;
	}

	ENQUEUE_RENDER_COMMAND(DrawGlobalShaderTestCommand)(
		[ TextureRenderTargetResource, Color, FeatureLevel](FRHICommandListImmediate& RHICmdList)
		{
			DrawRenderTarget_RenderThread(RHICmdList, TextureRenderTargetResource, Color, FeatureLevel);
		}
	);
}

void URTLibrary::DrawRenderTarget_RenderThread(FRHICommandListImmediate& RHICmdList, FTextureRenderTargetResource* OutRenderTargetResource,
                                               const FLinearColor& TextureColor, ERHIFeatureLevel::Type FeatureLevel)
{
    // 获取渲染目标纹理
    FRHITexture2D* RenderTargetTexture = OutRenderTargetResource->GetRenderTargetTexture();
    RHICmdList.Transition(FRHITransitionInfo(RenderTargetTexture, ERHIAccess::SRVMask, ERHIAccess::RTV));

    // 设置渲染通过信息
    FRHIRenderPassInfo RPInfo(RenderTargetTexture, ERenderTargetActions::DontLoad_Store);
    RHICmdList.BeginRenderPass(RPInfo, TEXT("Render Target Function"));
    {
        // 获取全局着色器映射
        FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(FeatureLevel);
        TShaderMapRef<FRenderTargetNewVS> VertexShader(GlobalShaderMap);
        TShaderMapRef<FRenderTargetNewPS> PixelShader(GlobalShaderMap);

        // 初始化并设置图形管线状态
        FGraphicsPipelineStateInitializer GraphicsPSOInit;
        RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
        GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
        GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
        GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
        GraphicsPSOInit.PrimitiveType = PT_TriangleStrip;
        GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GetVertexDeclarationFVector4();
        GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
        GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
    	SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit, 0);

    	
    	RHICmdList.SetViewport(0, 0, 0.f, OutRenderTargetResource->GetSizeX(), OutRenderTargetResource->GetSizeY(),
								   1.f);

    	FRHIBatchedShaderParameters BatchedParameters = RHICmdList.GetScratchShaderParameters();
    	PixelShader->SetParameters(BatchedParameters, TextureColor);
    	RHICmdList.SetBatchedShaderParameters(PixelShader.GetPixelShader(), BatchedParameters);
    	
        RHICmdList.DrawPrimitive(0, 2, 1);
    }
    RHICmdList.EndRenderPass();

    // 恢复资源访问权限
    RHICmdList.Transition(FRHITransitionInfo(RenderTargetTexture, ERHIAccess::RTV, ERHIAccess::SRVMask));
}
