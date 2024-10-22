// Fill out your copyright notice in the Description page of Project Settings.


#include "RenderTargetSubsystem.h"
#include "RenderTargetSceneViewExtension.h"

void URenderTargetSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	// CustomSceneViewExtension = FSceneViewExtensions::NewExtension<RenderTargetSceneViewExtension>();
	// if(UTextureRenderTarget2D* RenderTarget = LoadObject<UTextureRenderTarget2D>(nullptr, TEXT("/Game/ComputerShader/RT_GroupUV"))) {
	// 	TSharedPtr<RenderTargetSceneViewExtension> RenderTargetExtension = StaticCastSharedPtr<RenderTargetSceneViewExtension>(CustomSceneViewExtension);
	// 	if (RenderTargetExtension.IsValid()) {
	// 		RenderTargetExtension->SetRenderTarget(RenderTarget);
	// 	}
	// }
}

void URenderTargetSubsystem::Deinitialize()
{
	Super::Deinitialize();
	CustomSceneViewExtension.Reset();
	CustomSceneViewExtension = nullptr;
}
