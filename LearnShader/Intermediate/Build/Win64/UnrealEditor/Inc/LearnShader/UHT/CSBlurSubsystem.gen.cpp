// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LearnShader/ComputerShader/CSBlurSubsystem.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCSBlurSubsystem() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UEngineSubsystem();
ENGINE_API UClass* Z_Construct_UClass_UTextureRenderTarget2D_NoRegister();
LEARNSHADER_API UClass* Z_Construct_UClass_UCSBlurSubsystem();
LEARNSHADER_API UClass* Z_Construct_UClass_UCSBlurSubsystem_NoRegister();
UPackage* Z_Construct_UPackage__Script_LearnShader();
// End Cross Module References

// Begin Class UCSBlurSubsystem
void UCSBlurSubsystem::StaticRegisterNativesUCSBlurSubsystem()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCSBlurSubsystem);
UClass* Z_Construct_UClass_UCSBlurSubsystem_NoRegister()
{
	return UCSBlurSubsystem::StaticClass();
}
struct Z_Construct_UClass_UCSBlurSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "ComputerShader/CSBlurSubsystem.h" },
		{ "ModuleRelativePath", "ComputerShader/CSBlurSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RenderTargetSource_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// The source render target texture asset\n" },
#endif
		{ "ModuleRelativePath", "ComputerShader/CSBlurSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The source render target texture asset" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RenderTargetSource;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCSBlurSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCSBlurSubsystem_Statics::NewProp_RenderTargetSource = { "RenderTargetSource", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCSBlurSubsystem, RenderTargetSource), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RenderTargetSource_MetaData), NewProp_RenderTargetSource_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCSBlurSubsystem_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCSBlurSubsystem_Statics::NewProp_RenderTargetSource,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCSBlurSubsystem_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UCSBlurSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UEngineSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_LearnShader,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCSBlurSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UCSBlurSubsystem_Statics::ClassParams = {
	&UCSBlurSubsystem::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UCSBlurSubsystem_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UCSBlurSubsystem_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCSBlurSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_UCSBlurSubsystem_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UCSBlurSubsystem()
{
	if (!Z_Registration_Info_UClass_UCSBlurSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCSBlurSubsystem.OuterSingleton, Z_Construct_UClass_UCSBlurSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UCSBlurSubsystem.OuterSingleton;
}
template<> LEARNSHADER_API UClass* StaticClass<UCSBlurSubsystem>()
{
	return UCSBlurSubsystem::StaticClass();
}
UCSBlurSubsystem::UCSBlurSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UCSBlurSubsystem);
UCSBlurSubsystem::~UCSBlurSubsystem() {}
// End Class UCSBlurSubsystem

// Begin Registration
struct Z_CompiledInDeferFile_FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_ComputerShader_CSBlurSubsystem_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCSBlurSubsystem, UCSBlurSubsystem::StaticClass, TEXT("UCSBlurSubsystem"), &Z_Registration_Info_UClass_UCSBlurSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCSBlurSubsystem), 4264516638U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_ComputerShader_CSBlurSubsystem_h_2209875194(TEXT("/Script/LearnShader"),
	Z_CompiledInDeferFile_FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_ComputerShader_CSBlurSubsystem_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_ComputerShader_CSBlurSubsystem_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
