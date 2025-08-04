// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MeshReplaceMaterials.generated.h"

/**
 * 
 */
UCLASS()
class TOOLEXAMPLE_API UMeshReplaceMaterials : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Material Replacer")
	UMaterialInterface* Material;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Replacer")
	UStaticMesh* StaticMesh;

	FReply ButtonCallBack()
	{
		if (!Material || !StaticMesh)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hello ButtonCallBack!"));
			return FReply::Handled();
		}
	
		// 修改网格体
		StaticMesh->Modify();

		int32 NumMaterialSlots = StaticMesh->GetStaticMaterials().Num();
	
		for (int32 i = 0; i < NumMaterialSlots; ++i)
		{
			StaticMesh->SetMaterial(i, Material);
		}
		auto Dirty =  StaticMesh->MarkPackageDirty();

		GEditor->EndTransaction();
		StaticMesh->PostEditChange();
		
		return FReply::Handled();
	}
};
