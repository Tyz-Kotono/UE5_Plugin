#pragma once
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"


#define SLATE_IMAGE_BRUSH_PNG( ImagePath, ImageSize ) \
new FSlateImageBrush( SlateStyleSet->RootToContentDir( TEXT(ImagePath), TEXT(".png") ), ImageSize) 

#define SLATE_IMAGE_BRUSH_JPG( ImagePath, ImageSize ) \
new FSlateImageBrush( SlateStyleSet->RootToContentDir( TEXT(ImagePath), TEXT(".jpg") ), ImageSize)

const FVector2D Icon128(128.f, 128.f);
const FVector2D Icon64(64.f, 64.f);
const FVector2D Icon40(40.0f, 40.0f);
const FVector2D Icon20(20.0f, 20.0f);
const FVector2D Icon16(16.0f, 16.0f);
const FVector2D Icon12(12.0f, 12.0f);

class ExampleSlateStyle
{
public:
	static void Register()
	{
		if (StyleSet.IsValid())
		{
			return;
		}
		StyleSet = CreateSlateStyleSet();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
	}

	static void Unregister()
	{
		if (StyleSet.IsValid())
		{
			FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
			StyleSet.Reset();
		}
	}

private:
	inline static TSharedPtr<FSlateStyleSet> StyleSet = nullptr;
	inline static FString StyleRoot;
	inline static const FName StyleSetName = FName("TAStyle");


	static TSharedRef<FSlateStyleSet> CreateSlateStyleSet()
	{
		const FString PluginContentDir = IPluginManager::Get().FindPlugin(TEXT("ToolExample"))->GetBaseDir();
		const FString RootPath = FPaths::Combine(PluginContentDir, TEXT("Resources"));
		TSharedRef<FSlateStyleSet> SlateStyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));

		StyleRoot = RootPath;
		SlateStyleSet->SetContentRoot(RootPath);

		SlateStyleSet->Set("Mortis.Cucumber", SLATE_IMAGE_BRUSH_JPG("MortisCucumber", Icon128));
		SlateStyleSet->Set("Mortis.Drink", SLATE_IMAGE_BRUSH_JPG("MortisDrink", Icon64));
		SlateStyleSet->Set("Mortis", SLATE_IMAGE_BRUSH_JPG("Mortis", Icon64));
		return SlateStyleSet;
	}
};
