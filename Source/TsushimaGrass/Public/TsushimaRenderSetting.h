// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TsushimaRenderSetting.generated.h"

/**
 * 
 */
UCLASS()
class TSUSHIMAGRASS_API UTsushimaRenderSetting : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Render|Base")
	bool EnableBaseRender;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Render|Base")
	FLinearColor ScreenColor;
	
	UPROPERTY(BlueprintReadWrite, editAnywhere)
	TWeakObjectPtr<UTextureRenderTarget2D> GrassPositionRT;
	UPROPERTY(BlueprintReadWrite, editAnywhere)
	TWeakObjectPtr<UTextureRenderTarget2D> GrassNormalRT;
	UPROPERTY(BlueprintReadWrite, editAnywhere)
	float MinPoint;
	UPROPERTY(BlueprintReadWrite, editAnywhere)
	float GrassCurve;
	UPROPERTY(BlueprintReadWrite, editAnywhere)
	float CenterWidth;
	UPROPERTY(BlueprintReadWrite, editAnywhere)
	float ButtonWidth;
	
	// ===== 草叶渲染参数（对应 MidribRimData） =====
	
	// R: Rim Position - 边缘光起始位置（范围 0-1，默认 0.5）
	// 控制边缘光效果开始的位置，值越小边缘光越靠近中心
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Render|Grass|Midrib", meta=(ClampMin="0.0", ClampMax="1.0", UIMin="0.0", UIMax="1.0"))
	float RimPosition = 0.5f;
	
	// G: Rim Softness - 边缘柔和度（范围 0-1，默认 0.539）
	// 控制边缘光的过渡宽度，值越大边缘过渡越柔和
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Render|Grass|Midrib", meta=(ClampMin="0.0", ClampMax="1.0", UIMin="0.0", UIMax="1.0"))
	float RimSoftness = 0.539f;
	
	// B: Midrib Softness - 中脉宽度（范围 0-0.5，默认 0.15）
	// 控制草叶中心高亮线的宽度，值越大中脉越宽
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Render|Grass|Midrib", meta=(ClampMin="0.0", ClampMax="0.5", UIMin="0.0", UIMax="0.5"))
	float MidribSoftness = 0.15f;
	
	// A: Rim Intensity - 边缘光强度（范围 0-30，默认 22.0）
	// 控制边缘光的总强度，值越大边缘光越亮
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Render|Grass|Midrib", meta=(ClampMin="0.0", ClampMax="30.0", UIMin="0.0", UIMax="30.0"))
	float RimIntensity = 22.0f;
};
