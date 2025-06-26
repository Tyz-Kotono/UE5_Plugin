#include "RenderTargetShader.h"
IMPLEMENT_SHADER_TYPE(, FRenderTargetNewVS, TEXT("/TAShader/Example/RenderTargetShader.usf"), TEXT("MainVertexS"), SF_Vertex);
IMPLEMENT_SHADER_TYPE(, FRenderTargetNewPS, TEXT("/TAShader/Example/RenderTargetShader.usf"), TEXT("MainPixelS"), SF_Pixel);

IMPLEMENT_SHADER_TYPE(, FRenderTargetPS, TEXT("/TAShader/Example/RenderTargetShader.usf"), TEXT("MainPS"), SF_Pixel);
