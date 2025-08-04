// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FToolExampleModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	//LevelMenu
	void RegisterLevelMenu();
	
	//SlateStyle
	TSharedRef<FSlateStyleSet> CreateSlateStyleSet();

};
