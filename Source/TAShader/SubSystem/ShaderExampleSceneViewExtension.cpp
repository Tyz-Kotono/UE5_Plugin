#include "ShaderExampleSceneViewExtension.h"


#include "PixelShaderUtils.h"
#include "RenderTargetPool.h"
#include "SceneRenderTargetParameters.h"
#include "ShaderExampleDataAsset.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Runtime/Renderer/Internal/PostProcess/PostProcessInputs.h"
#include "Runtime/Renderer/Private/SceneRendering.h"
#include "ShaderExample/Shader/BaseShaderPS.h"
#include "TAShader/Shader/CSBlurShader.h"
#include "TAShader/Shader/RenderTargetShader.h"

DECLARE_GPU_DRAWCALL_STAT(BasePass);
DECLARE_GPU_DRAWCALL_STAT(RenderTargetPass);
DECLARE_GPU_DRAWCALL_STAT(ComputerShaderBlurPass);

#pragma region BaseFunction
FShaderExampleSceneViewExtension::FShaderExampleSceneViewExtension(const FAutoRegister& AutoRegister): FSceneViewExtensionBase(AutoRegister){}


FShaderExampleSceneViewExtension::~FShaderExampleSceneViewExtension()
{
}

void FShaderExampleSceneViewExtension::SetupViewFamily(FSceneViewFamily& InViewFamily)
{
	FSceneViewExtensionBase::SetupViewFamily(InViewFamily);
}

void FShaderExampleSceneViewExtension::SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView)
{
	FSceneViewExtensionBase::SetupView(InViewFamily, InView);
}

void FShaderExampleSceneViewExtension::BeginRenderViewFamily(FSceneViewFamily& InViewFamily)
{
	FSceneViewExtensionBase::BeginRenderViewFamily(InViewFamily);
}
#pragma endregion

#pragma region Global Main Function
void FShaderExampleSceneViewExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder,
	const FSceneView& View, const FPostProcessingInputs& Inputs)
{
	FSceneViewExtensionBase::PrePostProcessPass_RenderThread(GraphBuilder, View, Inputs);

	
	
	if(ExampleData == nullptr)
	{
		return;
	}


	checkSlow(View.bIsViewInfo);
	const FIntRect Viewport = static_cast<const FViewInfo&>(View).ViewRect;
	const FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);
	
	if(ExampleData->EnableBaseRender)
	{
		BaseGlobalShader_RenderThread(GraphBuilder, View, Inputs,Viewport,GlobalShaderMap);
	}

	if(ExampleData->EnableRenderTarget)
	{
		RenderTarget_RenderThread(GraphBuilder, View, Inputs,Viewport,GlobalShaderMap);
	}
	if(ExampleData->EnableComputerShader)
	{
		ComputerShaderBlur_RenderThread(GraphBuilder, View, Inputs,Viewport,GlobalShaderMap);
	}
}


void FShaderExampleSceneViewExtension::SetExampleData(UShaderExampleDataAsset* Data)
{
	ExampleData = Data;
}
#pragma endregion

#pragma region Base Global Draw Color to Screen	
void FShaderExampleSceneViewExtension::BaseGlobalShader_RenderThread(FRDGBuilder& GraphBuilder,
                                                              const FSceneView& View, const FPostProcessingInputs& Inputs,FIntRect Viewport,const FGlobalShaderMap* GlobalShaderMap)
{
	// UE_LOG(LogTemp, Warning, TEXT("这是一个调试信息！"));
	//Unreal Insights
	RDG_GPU_STAT_SCOPE(GraphBuilder,BasePass);
	// RenderDoc
	RDG_EVENT_SCOPE(GraphBuilder,"Base Pass");
	
	//抓取场景纹理
	const FSceneTextureShaderParameters SceneTextures = CreateSceneTextureShaderParameters(GraphBuilder, View, ESceneTextureSetupMode::SceneColor | ESceneTextureSetupMode::GBuffers);
	// 这是实际上带有阴影和阴影的颜色
	const FScreenPassTexture SceneColourTexture((*Inputs.SceneTextures)->SceneColorTexture, Viewport);

	FLinearColor Color =  ExampleData->ScreenColor;
	FVector3f ScreenColor = FVector3f(Color.R,Color.G,Color.B);
	
	//设置Global Shader 数据，分配内存
	FBaseShaderPS::FParameters* Parameters = GraphBuilder.AllocParameters<FBaseShaderPS::FParameters>();
	Parameters->SceneColorTexture = SceneColourTexture.Texture;
	Parameters->SceneTextures = SceneTextures;
	Parameters->TargetColour = ScreenColor;
	// Parameters->View = View.ViewUniformBuffer;

	//设置RenderTarget 和 Return Texture
	Parameters->RenderTargets[0] = FRenderTargetBinding((*Inputs.SceneTextures)->SceneColorTexture, ERenderTargetLoadAction::ELoad);

	TShaderMapRef<FBaseShaderPS> PixelShader(GlobalShaderMap);


	FPixelShaderUtils::AddFullscreenPass(GraphBuilder, GlobalShaderMap, FRDGEventName(TEXT("Base Pass")), PixelShader, Parameters, Viewport);
}
#pragma endregion

#pragma region Render Target Texture

void FShaderExampleSceneViewExtension::RenderTarget_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View,
	const FPostProcessingInputs& Inputs, FIntRect Viewport, const FGlobalShaderMap* GlobalShaderMap)
{
	if (ExampleData->RenderTexture == nullptr)
	{
		return;
	}
	if (!PooledRenderTarget.IsValid())
	{
		CreatePooledRenderTarget_RenderThread();
	}
	//Unreal Insights
	RDG_GPU_STAT_SCOPE(GraphBuilder,RenderTargetPass);
	// RenderDoc
	RDG_EVENT_SCOPE(GraphBuilder,"Render Target Pass");
	
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

void FShaderExampleSceneViewExtension::CreatePooledRenderTarget_RenderThread()
{
	//是否在渲染线程或 RHI 线程中
	checkf(IsInRenderingThread() || IsInRHIThread(), TEXT("Cannot create from outside the rendering thread"));

	//渲染目标资源需要渲染线程
	// Render target resources require the render thread
	const FTextureRenderTargetResource* RenderTargetResource = ExampleData->RenderTexture->GetRenderTargetResource();

	if (RenderTargetResource == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Render Target Resource is null"));
	}

	//获取RHI 引用
	//获取渲染目标纹理的 RHI 引用
	//将纹理绑定到渲染管线上
	//可以使用 RHI 引用来创建、更新或销毁纹理
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


#pragma endregion

#pragma region ComputerShader Draw Blur

void FShaderExampleSceneViewExtension::ComputerShaderBlur_RenderThread(FRDGBuilder& GraphBuilder,
	const FSceneView& View, const FPostProcessingInputs& Inputs, FIntRect Viewport,
	const FGlobalShaderMap* GlobalShaderMap)
{
	checkf(IsInRenderingThread() || IsInRHIThread(), TEXT("Cannot create from outside the rendering thread"));

	// 抓取场景纹理
	const FSceneTextureShaderParameters SceneTextures = CreateSceneTextureShaderParameters(GraphBuilder, View, ESceneTextureSetupMode::SceneColor | ESceneTextureSetupMode::GBuffers);
	const FScreenPassTexture SceneColourTexture((*Inputs.SceneTextures)->SceneColorTexture, Viewport);

	// RenderDoc 调试信息
	RDG_GPU_STAT_SCOPE(GraphBuilder, ComputerShaderBlur Pass);
	RDG_EVENT_SCOPE(GraphBuilder, "Compute Shader Blur");

	// 创建临时纹理来存储模糊后的结果
	FRDGTextureRef TempTexture = GraphBuilder.CreateTexture(SceneColourTexture.Texture->Desc, TEXT("TempTexture"));
	FRDGTextureUAVRef TempUAV = GraphBuilder.CreateUAV(FRDGTextureUAVDesc(TempTexture));

	// 设置着色器参数
	FCSBlurShader::FParameters* Parameters = GraphBuilder.AllocParameters<FCSBlurShader::FParameters>();
	Parameters->SceneColorSampler = TStaticSamplerState<SF_Bilinear, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI();
	Parameters->SceneColorTexture = SceneColourTexture.Texture;
	Parameters->OutputTexture = TempUAV;  // 模糊后的结果存储到临时纹理中

	// 设置线程组数
	const FIntPoint ThreadCount = Viewport.Size();
	const FIntVector GroupCount = FComputeShaderUtils::GetGroupCount(ThreadCount, FIntPoint(16, 16));
	
	// 调用模糊的计算着色器
	TShaderMapRef<FCSBlurShader> ComputeShader(GlobalShaderMap);
	FComputeShaderUtils::AddPass(GraphBuilder, FRDGEventName(TEXT("Blur Compute Pass")), ERDGPassFlags::Compute, ComputeShader, Parameters, GroupCount);

	// 将模糊后的结果拷贝回场景颜色纹理
	AddCopyTexturePass(GraphBuilder, TempTexture, SceneColourTexture.Texture);
}

#pragma endregion