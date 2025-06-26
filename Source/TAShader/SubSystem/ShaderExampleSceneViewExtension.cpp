#include "ShaderExampleSceneViewExtension.h"

#include "ShaderExampleSubsystem.h"
#include "PixelShaderUtils.h"
#include "SceneRenderTargetParameters.h"
#include "ShaderExampleDataAsset.h"
#include "Runtime/Renderer/Internal/PostProcess/PostProcessInputs.h"
#include "Runtime/Renderer/Private/SceneRendering.h"
#include "ShaderExample/Shader/BaseShaderPS.h"
#include "ShaderExample/Shader/LearnShaderPS.h"

DECLARE_GPU_DRAWCALL_STAT(BasePass);
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
	
		BaseGlobalShaderRender(GraphBuilder, View, Inputs,Viewport,GlobalShaderMap);
	}
	
}


void FShaderExampleSceneViewExtension::SetExampleData(UShaderExampleDataAsset* Data)
{
	ExampleData = Data;
}

void FShaderExampleSceneViewExtension::BaseGlobalShaderRender(FRDGBuilder& GraphBuilder,
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
