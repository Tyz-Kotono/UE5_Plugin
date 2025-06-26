#include "RenderTargetSceneViewExtension.h"

#include "RenderTargetPool.h"
#include "RenderTargetShader.h"
#include "PixelShaderUtils.h"
#include "SceneTexturesConfig.h"
#include "RenderGraphBuilder.h"
#include "Engine/TextureRenderTarget2D.h"
#include "PostProcess/PostProcessInputs.h"
#include "Runtime/Renderer/Private/SceneRendering.h"

RenderTargetSceneViewExtension::RenderTargetSceneViewExtension(const FAutoRegister& AutoRegister):
	FSceneViewExtensionBase(AutoRegister)
{
}

RenderTargetSceneViewExtension::~RenderTargetSceneViewExtension()
{
}

void RenderTargetSceneViewExtension::SetupViewFamily(FSceneViewFamily& InViewFamily)
{
}

void RenderTargetSceneViewExtension::SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView)
{
}

void RenderTargetSceneViewExtension::BeginRenderViewFamily(FSceneViewFamily& InViewFamily)
{
}

void RenderTargetSceneViewExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View,
                                                                     const FPostProcessingInputs& Inputs)
{
	FSceneViewExtensionBase::PrePostProcessPass_RenderThread(GraphBuilder, View, Inputs);

	if (RenderTargetSource == nullptr)
	{
		return;
	}

	if (!PooledRenderTarget.IsValid())
	{
		// Only needs to be done once
		// However, if you modify the render target asset, eg: change the resolution or pixel format, you may need to recreate the PooledRenderTarget object
		//只需要执行一次

		//但是，如果你修改渲染目标资源，例如：改变分辨率或像素格式，你可能需要重新创建PooledRenderTarget对象
		CreatePooledRenderTarget_RenderThread();
	}

	checkSlow(View.bIsViewInfo);
	const FIntRect Viewport = static_cast<const FViewInfo&>(View).ViewRect;
	const FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);
	const FScreenPassTexture SceneColourTexture((*Inputs.SceneTextures)->SceneColorTexture, Viewport);

	// Needs to be registered every frame
	FRDGTextureRef RenderTargetTexture = GraphBuilder.RegisterExternalTexture(
		PooledRenderTarget, TEXT("Bound Render Target"));
	// Since we're rendering to the render target, we're going to use the full size of the render target rather than the screen
	//因为我们渲染到渲染目标，我们将使用渲染目标的完整尺寸，而不是屏幕
	const FIntRect RenderViewport = FIntRect(0, 0, RenderTargetTexture->Desc.Extent.X,
	                                         RenderTargetTexture->Desc.Extent.Y);


	// 获取参数随后设置
	FRenderTargetPS::FParameters* Parameters = GraphBuilder.AllocParameters<FRenderTargetPS::FParameters>();
	Parameters->TextureSize = RenderTargetTexture->Desc.Extent;
	Parameters->SceneColorSampler = TStaticSamplerState<SF_Bilinear, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI();
	Parameters->SceneColorTexture = SceneColourTexture.Texture;
	// We're going to also clear the render target


	Parameters->RenderTargets[0] = FRenderTargetBinding(RenderTargetTexture, ERenderTargetLoadAction::EClear);

	//获取全局Shader
	TShaderMapRef<FRenderTargetPS> PixelShader(GlobalShaderMap);
	//添加到RDG
	//开始渲染
	FPixelShaderUtils::AddFullscreenPass
	(
		GraphBuilder,
		GlobalShaderMap,
		FRDGEventName(TEXT("Render Target Pass")),
		PixelShader,
		Parameters,
		RenderViewport
	);
}

void RenderTargetSceneViewExtension::SetRenderTarget(UTextureRenderTarget2D* RenderTarget)
{
	RenderTargetSource = RenderTarget;
}

void RenderTargetSceneViewExtension::CreatePooledRenderTarget_RenderThread()
{
	//是否在渲染线程或 RHI 线程中
	checkf(IsInRenderingThread() || IsInRHIThread(), TEXT("Cannot create from outside the rendering thread"));

	//渲染目标资源需要渲染线程
	// Render target resources require the render thread
	const FTextureRenderTargetResource* RenderTargetResource = RenderTargetSource->GetRenderTargetResource();

	if (RenderTargetResource == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Render Target Resource is null"));
	}

	//获取RHI 引用
	//获取渲染目标纹理的 RHI 引用
	//将纹理绑定到渲染管线上
	//可以使用 RHI 引用来创建、更新或销毁纹理,duqu xieru 
	const FTexture2DRHIRef RenderTargetRHI = RenderTargetResource->GetRenderTargetTexture();
	if (RenderTargetRHI.GetReference() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Render Target RHI is null"));
	}

	//渲染目标秒速
	FSceneRenderTargetItem RenderTargetItem;
	//渲染目标  被着色器作为资源访问
	RenderTargetItem.TargetableTexture = RenderTargetRHI;
	RenderTargetItem.ShaderResourceTexture = RenderTargetRHI;

	// Flags allow it to be used as a render target, shader resource, UAV
	//标志允许它被用作渲染目标，着色器资源，无人机
	FPooledRenderTargetDesc RenderTargetDesc = FPooledRenderTargetDesc::Create2DDesc(
		RenderTargetResource->GetSizeXY(), RenderTargetRHI->GetDesc().Format,
		FClearValueBinding::Black,
		TexCreate_RenderTargetable | TexCreate_ShaderResource | TexCreate_UAV, TexCreate_None, false);

	//创建一个新的池化渲染目标。这个方法的参数包括渲染目标的描述对象
	GRenderTargetPool.CreateUntrackedElement(RenderTargetDesc, PooledRenderTarget, RenderTargetItem);

	//创建了未跟踪的Pooled渲染目标资源
	UE_LOG(LogTemp, Warning, TEXT("Created untracked Pooled Render Target resource"));
}
