#include "FCSBlurSceneViewExtension.h"

#include "CSBlurShader.h"
#include "PixelShaderUtils.h"
#include "LearnShader/Rendering/LearnShaderPS.h"
#include "PostProcess/PostProcessInputs.h"
#include "Runtime/Renderer/Private/SceneRendering.h"


FCSBlurSceneViewExtension::FCSBlurSceneViewExtension(const FAutoRegister& AutoRegister): FSceneViewExtensionBase(AutoRegister)
{
}

FCSBlurSceneViewExtension::~FCSBlurSceneViewExtension()
{
}

DECLARE_GPU_DRAWCALL_STAT(ComputerShaderBlur);
void FCSBlurSceneViewExtension::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs)
{
	FSceneViewExtensionBase::PrePostProcessPass_RenderThread(GraphBuilder, View, Inputs);

	checkf(IsInRenderingThread() || IsInRHIThread(), TEXT("Cannot create from outside the rendering thread"));

	checkSlow(View.bIsViewInfo);
	const FIntRect Viewport = static_cast<const FViewInfo&>(View).ViewRect;
	const FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);

	// 抓取场景纹理
	const FSceneTextureShaderParameters SceneTextures = CreateSceneTextureShaderParameters(GraphBuilder, View, ESceneTextureSetupMode::SceneColor | ESceneTextureSetupMode::GBuffers);
	const FScreenPassTexture SceneColourTexture((*Inputs.SceneTextures)->SceneColorTexture, Viewport);

	// RenderDoc 调试信息
	RDG_GPU_STAT_SCOPE(GraphBuilder, ComputerShaderBlur);
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
	// 最终将结果渲染到屏幕上
	// AddResolveSceneColorPass(GraphBuilder, View,TempTexture);  // 确保模糊结果最终渲染到屏幕
