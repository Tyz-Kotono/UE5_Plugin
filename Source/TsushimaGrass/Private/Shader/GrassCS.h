// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

struct FPostProcessingInputs;
class UTsushimaRenderSetting;

class TSUSHIMAGRASS_API FTsushimaGrassInterface
{
public:
	static void AddPass_RenderThread(
		FRDGBuilder& GraphBuilder,
		const FSceneView& View,
		const FPostProcessingInputs& Inputs,
		UTsushimaRenderSetting* InGrassSpec,
		TRefCountPtr<IPooledRenderTarget>& PooledPersistentRT,
		int32& CacheResolution);
	
	static void Grass_RenderThread(
		FRDGBuilder& GraphBuilder,
		const FGlobalShaderMap* ShaderMap,
		uint32 Resolution,
		const UTsushimaRenderSetting* GrassSpec,
		FRDGTextureRef PreviousTexture,
		FRDGTextureRef OutputTextureRef);
	
	static void ResetPersistentResources(TRefCountPtr<IPooledRenderTarget>& PooledPersistentRT);
};
