#include "RenderTargetShader.h"
IMPLEMENT_SHADER_TYPE(, FRenderTargetNewVS, TEXT("/LearnShader/Private/RenderTargetShader.usf"), TEXT("MainVertexS"), SF_Vertex);
IMPLEMENT_SHADER_TYPE(, FRenderTargetNewPS, TEXT("/LearnShader/Private/RenderTargetShader.usf"), TEXT("MainPixelS"), SF_Pixel);

IMPLEMENT_SHADER_TYPE(, FRenderTargetPS, TEXT("/LearnShader/Private/RenderTargetShader.usf"), TEXT("MainPS"), SF_Pixel);
