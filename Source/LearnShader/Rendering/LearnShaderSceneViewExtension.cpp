#include "LearnShaderSceneViewExtension.h"

#include "PixelShaderUtils.h"
#include "LearnShader/Rendering/LearnShaderPS.h"
#include "PostProcess/PostProcessInputs.h"
#include "Runtime/Renderer/Private/SceneRendering.h"

DECLARE_GPU_DRAWCALL_STAT(ColourMix);

LearnShaderSceneViewExtension::LearnShaderSceneViewExtension(const FAutoRegister& AutoRegister): FSceneViewExtensionBase(AutoRegister){}
LearnShaderSceneViewExtension::~LearnShaderSceneViewExtension(){}
void LearnShaderSceneViewExtension::SetupViewFamily(FSceneViewFamily& InViewFamily){}
void LearnShaderSceneViewExtension::SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView){}
void LearnShaderSceneViewExtension::BeginRenderViewFamily(FSceneViewFamily& InViewFamily){}

void LearnShaderSceneViewExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View,
	const FPostProcessingInputs& Inputs)
{
	FSceneViewExtensionBase::PrePostProcessPass_RenderThread(GraphBuilder, View, Inputs);
	
	checkSlow(View.bIsViewInfo);
	const FIntRect Viewport = static_cast<const FViewInfo&>(View).ViewRect;
	const FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);

	//跟踪分析
	
	//Unreal Insights
	RDG_GPU_STAT_SCOPE(GraphBuilder,ColourMix);
	// RenderDoc
	RDG_EVENT_SCOPE(GraphBuilder,"Colour Mix");
	
	//抓取场景纹理
	const FSceneTextureShaderParameters SceneTextures = CreateSceneTextureShaderParameters(GraphBuilder, View, ESceneTextureSetupMode::SceneColor | ESceneTextureSetupMode::GBuffers);
	// 这是实际上带有阴影和阴影的颜色
	const FScreenPassTexture SceneColourTexture((*Inputs.SceneTextures)->SceneColorTexture, Viewport);


	//设置Global Shader 数据，分配内存
	FLearnShaderPS::FParameters* Parameters = GraphBuilder.AllocParameters<FLearnShaderPS::FParameters>();
	Parameters->SceneColorTexture = SceneColourTexture.Texture;
	Parameters->SceneTextures = SceneTextures;
	Parameters->TargetColour = FVector3f(1.0f, 0.0f, 1.0f);
	// Parameters->View = View.ViewUniformBuffer;

	//设置RenderTarget 和 Return Texture
	Parameters->RenderTargets[0] = FRenderTargetBinding((*Inputs.SceneTextures)->SceneColorTexture, ERenderTargetLoadAction::ELoad);

	TShaderMapRef<FLearnShaderPS> PixelShader(GlobalShaderMap);
	FPixelShaderUtils::AddFullscreenPass(GraphBuilder, GlobalShaderMap, FRDGEventName(TEXT("Colour Mix Pass")), PixelShader, Parameters, Viewport);

}
