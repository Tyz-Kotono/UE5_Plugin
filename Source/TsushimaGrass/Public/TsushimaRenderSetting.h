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
	TWeakObjectPtr<UTextureRenderTarget2D> GrassRT;
	UPROPERTY(BlueprintReadWrite, editAnywhere)
	float MinPoint;
	UPROPERTY(BlueprintReadWrite, editAnywhere)
	float GrassCurve;
	UPROPERTY(BlueprintReadWrite, editAnywhere)
	float CenterWidth;
	UPROPERTY(BlueprintReadWrite, editAnywhere)
	float ButtonWidth;
};
