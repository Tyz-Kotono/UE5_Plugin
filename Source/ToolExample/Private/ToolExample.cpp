// Copyright Epic Games, Inc. All Rights Reserved.

#include "ToolExample.h"
#include "ToolExample/Commands/ExampleTCommands.h"
#include "ToolExample/Python/PythonTCommands.h"
#include "ToolExample/Slate/SlateTCommands.h"
#include "ToolExample/SlateStyle/ExampleSlateStyle.h"

#define LOCTEXT_NAMESPACE "FToolExampleModule"


void FToolExampleModule::StartupModule()
{
	ExampleSlateStyle::Register();
	RegisterLevelMenu();
}

void FToolExampleModule::ShutdownModule()
{
	ExampleSlateStyle::Unregister();
}

void FToolExampleModule::RegisterLevelMenu()
{
	//注册Command
	FExampleTCommands::Register();
	FSlateTCommands::Register();
	FPythonTCommands::Register();
	// 获取工具菜单
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.User");

	FToolMenuSection& Section = Menu->FindOrAddSection(NAME_None); 
	
	Section.AddEntry(FToolMenuEntry::InitSubMenu(
		"ExampleMenu",											// 子菜单名称
		LOCTEXT("Example_Label", "Example Label"),				// 子菜单的标签
		LOCTEXT("Example_Tooltip", "Example Tooltip"),			// 子菜单的 Tooltip
		FNewToolMenuChoice(), 
		FToolUIActionChoice(),
		EUserInterfaceActionType::Button,						// 这是一个按钮
		true,													// 点击时展开子菜单
		TAttribute<FSlateIcon>(FSlateIcon("TAStyle", "Mortis.Cucumber")),											//Icon
		true													// 选择后关闭窗口
	));

	static const FName BaseMenuName = "LevelEditor.LevelEditorToolBar.User.ExampleMenu";
	Menu = UToolMenus::Get()->RegisterMenu(BaseMenuName);
	// 创建一个新Section，用于添加菜单项
	FToolMenuSection& ExampleSection = Menu->AddSection("Example ", FText::FromString("Example"));
	ExampleSection.AddMenuEntryWithCommandList(FExampleTCommands::Get().CommandLogLambda, FExampleTCommands::Get().CommandList);
	ExampleSection.AddMenuEntryWithCommandList(FExampleTCommands::Get().CommandLogFunction, FExampleTCommands::Get().CommandList);

	FToolMenuSection& SlateSection = Menu->AddSection("Slate ", FText::FromString("Slate"));
	SlateSection.AddMenuEntryWithCommandList(FSlateTCommands::Get().OpenWindow, FSlateTCommands::Get().CommandList);
	SlateSection.AddMenuEntryWithCommandList(FSlateTCommands::Get().ReplaceMaterials, FSlateTCommands::Get().CommandList);
	SlateSection.AddMenuEntryWithCommandList(FSlateTCommands::Get().OpenMeshReplaceMaterialsWindow, FSlateTCommands::Get().CommandList);

	FToolMenuSection& PythonSection = Menu->AddSection("Python ", FText::FromString("Python"));
	PythonSection.AddMenuEntryWithCommandList(FPythonTCommands::Get().RunPython, FPythonTCommands::Get().CommandList);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToolExampleModule, ToolExample)