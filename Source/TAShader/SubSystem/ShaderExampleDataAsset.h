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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool EnableBaseRender;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor ScreenColor;
};
