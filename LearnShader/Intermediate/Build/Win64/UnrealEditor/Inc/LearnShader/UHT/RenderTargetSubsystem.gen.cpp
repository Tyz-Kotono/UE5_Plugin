// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LearnShader/RenderTarget/RenderTargetSubsystem.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRenderTargetSubsystem() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UEngineSubsystem();
LEARNSHADER_API UClass* Z_Construct_UClass_URenderTargetSubsystem();
LEARNSHADER_API UClass* Z_Construct_UClass_URenderTargetSubsystem_NoRegister();
UPackage* Z_Construct_UPackage__Script_LearnShader();
// End Cross Module References

// Begin Class URenderTargetSubsystem
void URenderTargetSubsystem::StaticRegisterNativesURenderTargetSubsystem()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(URenderTargetSubsystem);
UClass* Z_Construct_UClass_URenderTargetSubsystem_NoRegister()
{
	return URenderTargetSubsystem::StaticClass();
}
struct Z_Construct_UClass_URenderTargetSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "RenderTarget/RenderTargetSubsystem.h" },
		{ "ModuleRelativePath", "RenderTarget/RenderTargetSubsystem.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URenderTargetSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_URenderTargetSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UEngineSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_LearnShader,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URenderTargetSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_URenderTargetSubsystem_Statics::ClassParams = {
	&URenderTargetSubsystem::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URenderTargetSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_URenderTargetSubsystem_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_URenderTargetSubsystem()
{
	if (!Z_Registration_Info_UClass_URenderTargetSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_URenderTargetSubsystem.OuterSingleton, Z_Construct_UClass_URenderTargetSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_URenderTargetSubsystem.OuterSingleton;
}
template<> LEARNSHADER_API UClass* StaticClass<URenderTargetSubsystem>()
{
	return URenderTargetSubsystem::StaticClass();
}
URenderTargetSubsystem::URenderTargetSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR(URenderTargetSubsystem);
URenderTargetSubsystem::~URenderTargetSubsystem() {}
// End Class URenderTargetSubsystem

// Begin Registration
struct Z_CompiledInDeferFile_FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_RenderTarget_RenderTargetSubsystem_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_URenderTargetSubsystem, URenderTargetSubsystem::StaticClass, TEXT("URenderTargetSubsystem"), &Z_Registration_Info_UClass_URenderTargetSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URenderTargetSubsystem), 987247359U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_RenderTarget_RenderTargetSubsystem_h_3900372413(TEXT("/Script/LearnShader"),
	Z_CompiledInDeferFile_FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_RenderTarget_RenderTargetSubsystem_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_RenderTarget_RenderTargetSubsystem_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
