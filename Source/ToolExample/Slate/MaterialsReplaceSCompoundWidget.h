#pragma once
#include "ToolExample/DataView/MeshReplaceMaterials.h"
#include "ToolExample/Library/SlateFunctionLibrary.h"

class SMaterialsReplaceSCompoundWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMaterialsReplaceSCompoundWidget)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		auto DetailsObject = TStrongObjectPtr<UMeshReplaceMaterials>(
			NewObject<UMeshReplaceMaterials>());
		DetailsView = USlateFunctionLibrary::CreateDetailsView(DetailsObject.Get());
		ChildSlot
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(5, 0)
			[
				DetailsView.ToSharedRef()
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(10, 10)
			[
				SNew(SButton)
				.Text(FText::FromString(TEXT("材质循环替换")))
				.OnClicked_Lambda([DetailsObject]() -> FReply
				{
					return DetailsObject->ButtonCallBack();
				})
			]
		];
	}

private:
	TSharedPtr<IDetailsView> DetailsView;
};
