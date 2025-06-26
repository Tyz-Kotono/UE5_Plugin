// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ShaderExampleDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TASHADER_API UShaderExampleDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Render|Base")
	bool EnableBaseRender;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Render|Base")
	FLinearColor ScreenColor;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Render|RednerTarget")
	bool EnableRenderTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Render|RednerTarget")
	FLinearColor RenderTargetColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Render|RednerTarget")
	TObjectPtr<UTextureRenderTarget2D> RenderTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Render|ComputerShader")
	bool EnableComputerShader;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Render|ComputerShader")
	FLinearColor ComputerShaderColor;
	
};
