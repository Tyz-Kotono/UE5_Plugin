#include "SlateTCommands.h"

#include "MaterialsReplaceSCompoundWidget.h"
#include "PropertyCustomizationHelpers.h"

#define LOCTEXT_NAMESPACE "Slate TCommands"
TSharedRef<FUICommandList> FSlateTCommands::CommandList = MakeShareable(new FUICommandList);

FSlateTCommands::FSlateTCommands() : TCommands<FSlateTCommands>
(
	"Slate TCommands",
	NSLOCTEXT("Slate", "Slate Commands", "Example Plugin"),
	NAME_None,
	"TAStyle" //FXXXX::GetAppStyleSetName() // Icon
)
{
}

void FSlateTCommands::RegisterCommands()
{
	UI_COMMAND(OpenWindow, "Example Function", "Example Function ToolTip", EUserInterfaceActionType::Button,
	           FInputChord());
	CommandList->MapAction(OpenWindow, FExecuteAction::CreateRaw(this, &FSlateTCommands::OpenWindow_Function));

	UI_COMMAND(ReplaceMaterials, "Replace Materials", "Replace all materials on selected StaticMesh",
	           EUserInterfaceActionType::Button, FInputChord());

	CommandList->MapAction(
		ReplaceMaterials,
		FExecuteAction::CreateRaw(this, &FSlateTCommands::OpenReplacerWindow_Function)
	);

	UI_COMMAND(OpenMeshReplaceMaterialsWindow, "DataView Replace Materials", "DataView Replace all materials on selected StaticMesh",
			   EUserInterfaceActionType::Button, FInputChord());

	CommandList->MapAction(
		OpenMeshReplaceMaterialsWindow,
		FExecuteAction::CreateRaw(this, &FSlateTCommands::OpenMeshReplaceMaterialsWindow_Function)
	);
}

void FSlateTCommands::OpenWindow_Function()
{
	// 尝试获取现有窗口
	if (TSharedPtr<SWindow> ExistingWindow = OpenWindowPtr.Pin())
	{
		ExistingWindow->BringToFront();
		return;
	}

	// 创建新窗口
	TSharedRef<SWindow> NewWindow = SNew(SWindow)
		.ClientSize(FVector2D(600, 600))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Text(LOCTEXT("WelcomeText", "Hello Slate!"))
			]
		];

	// 绑定窗口关闭事件以清理弱引用
	NewWindow->SetOnWindowClosed(FOnWindowClosed::CreateLambda(
		[this](const TSharedRef<SWindow>&)
		{
			OpenWindowPtr.Reset(); // 窗口关闭时自动清除弱引用
		}));

	// 存储弱引用并显示窗口
	OpenWindowPtr = NewWindow;
	FSlateApplication::Get().AddWindow(NewWindow, true);
}

void FSlateTCommands::OpenReplacerWindow_Function()
{
	if (TSharedPtr<SWindow> ExistingWindow = ReplaceMaterialsWindowPtr.Pin())
	{
		ExistingWindow->BringToFront();
		return;
	}

	// 创建主窗口
	TSharedRef<SWindow> NewWindow = SNew(SWindow)
		.Title(LOCTEXT("MaterialReplacerTitle", "Material Replacer"))
		.ClientSize(FVector2D(500, 300))
		[
			SNew(SVerticalBox)

			// Mesh Picker
			+ SVerticalBox::Slot().AutoHeight().Padding(5)
			[
				SNew(SObjectPropertyEntryBox)
				.AllowedClass(UStaticMesh::StaticClass())
				.OnObjectChanged(this, &FSlateTCommands::OnMeshSelected)
				//切换时显示名字
				.ObjectPath_Lambda([this]() {
				   return SelectedMesh.IsValid() ? SelectedMesh->GetPathName() : TEXT("");
			   })
			]

			// Material Picker
			+ SVerticalBox::Slot().AutoHeight().Padding(5)
			[
				SNew(SObjectPropertyEntryBox)
				.AllowedClass(UMaterialInterface::StaticClass())
				.OnObjectChanged(this, &FSlateTCommands::OnMaterialSelected)
				.ObjectPath_Lambda([this]() {
				   return SelectedMaterial.IsValid() ? SelectedMaterial->GetPathName() : TEXT("");
			   })
			]

			// Replace Button
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(5)
			.HAlign(HAlign_Center)
			[
				SNew(SButton)
				.Text(FText::FromString(TEXT("Replace All Materials")))
				.OnClicked(this, &FSlateTCommands::OnReplaceMaterialsClicked)
			]
		];

	NewWindow->SetOnWindowClosed(FOnWindowClosed::CreateLambda(
		[this](const TSharedRef<SWindow>&)
		{
			OpenWindowPtr.Reset();
		}));

	OpenWindowPtr = NewWindow;
	FSlateApplication::Get().AddWindow(NewWindow, true);
}


void FSlateTCommands::OnMeshSelected(const FAssetData& AssetData)
{
	SelectedMesh = Cast<UStaticMesh>(AssetData.GetAsset());
}

void FSlateTCommands::OnMaterialSelected(const FAssetData& AssetData)
{
	SelectedMaterial = Cast<UMaterialInterface>(AssetData.GetAsset());
}

FReply FSlateTCommands::OnReplaceMaterialsClicked()
{
	if (!SelectedMesh.IsValid() || !SelectedMaterial.IsValid())
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Please select both a mesh and a material.")));
		return FReply::Handled();
	}
	
	// 替换所有材质槽
	for (int32 i = 0; i < SelectedMesh->GetStaticMaterials().Num(); ++i)
	{
		SelectedMesh->SetMaterial(i, SelectedMaterial.Get());
	}
	
	SelectedMesh->MarkPackageDirty();
	SelectedMesh->PostEditChange();
	SelectedMesh->Modify();
	
	// FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Materials replaced successfully.")));

	return FReply::Handled();
}

void FSlateTCommands::OpenMeshReplaceMaterialsWindow_Function()
{
	// 尝试获取现有窗口
	if (TSharedPtr<SWindow> ExistingWindow = OpenMeshReplaceMaterialsWindowPtr.Pin())
	{
		ExistingWindow->BringToFront();
		return;
	}

	// 创建新窗口
	TSharedRef<SWindow> NewWindow = SNew(SWindow)
		.ClientSize(FVector2D(600, 600))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				SNew(SMaterialsReplaceSCompoundWidget)
			]
		];

	// 绑定窗口关闭事件以清理弱引用
	NewWindow->SetOnWindowClosed(FOnWindowClosed::CreateLambda(
		[this](const TSharedRef<SWindow>&)
		{
			OpenWindowPtr.Reset(); // 窗口关闭时自动清除弱引用
		}));

	// 存储弱引用并显示窗口
	OpenMeshReplaceMaterialsWindowPtr = NewWindow;
	FSlateApplication::Get().AddWindow(NewWindow, true);
}


#undef LOCTEXT_NAMESPACE
