// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RTLibrary.generated.h"


UCLASS()
class LEARNSHADER_API URTLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "Render Liberay", meta = (WorldContext = "WorldContextObject"))
	static void DrawRenderTarget_Function(UTextureRenderTarget2D* OutRenderTarget, const FLinearColor Color,
								   const UObject* WorldActor);
	static void DrawRenderTarget_RenderThread(FRHICommandListImmediate& RHICmdList,FTextureRenderTargetResource* OutRenderTargetResource,
		const FLinearColor& InColor,ERHIFeatureLevel::Type FeatureLevel);
};
