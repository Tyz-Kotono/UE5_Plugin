// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LearnShader/Rendering/LearnShaderSubsystem.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLearnShaderSubsystem() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UEngineSubsystem();
LEARNSHADER_API UClass* Z_Construct_UClass_ULearnShaderSubsystem();
LEARNSHADER_API UClass* Z_Construct_UClass_ULearnShaderSubsystem_NoRegister();
UPackage* Z_Construct_UPackage__Script_LearnShader();
// End Cross Module References

// Begin Class ULearnShaderSubsystem
void ULearnShaderSubsystem::StaticRegisterNativesULearnShaderSubsystem()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ULearnShaderSubsystem);
UClass* Z_Construct_UClass_ULearnShaderSubsystem_NoRegister()
{
	return ULearnShaderSubsystem::StaticClass();
}
struct Z_Construct_UClass_ULearnShaderSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Rendering/LearnShaderSubsystem.h" },
		{ "ModuleRelativePath", "Rendering/LearnShaderSubsystem.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULearnShaderSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ULearnShaderSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UEngineSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_LearnShader,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULearnShaderSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ULearnShaderSubsystem_Statics::ClassParams = {
	&ULearnShaderSubsystem::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULearnShaderSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_ULearnShaderSubsystem_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ULearnShaderSubsystem()
{
	if (!Z_Registration_Info_UClass_ULearnShaderSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULearnShaderSubsystem.OuterSingleton, Z_Construct_UClass_ULearnShaderSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ULearnShaderSubsystem.OuterSingleton;
}
template<> LEARNSHADER_API UClass* StaticClass<ULearnShaderSubsystem>()
{
	return ULearnShaderSubsystem::StaticClass();
}
ULearnShaderSubsystem::ULearnShaderSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR(ULearnShaderSubsystem);
ULearnShaderSubsystem::~ULearnShaderSubsystem() {}
// End Class ULearnShaderSubsystem

// Begin Registration
struct Z_CompiledInDeferFile_FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_Rendering_LearnShaderSubsystem_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ULearnShaderSubsystem, ULearnShaderSubsystem::StaticClass, TEXT("ULearnShaderSubsystem"), &Z_Registration_Info_UClass_ULearnShaderSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULearnShaderSubsystem), 843554583U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_Rendering_LearnShaderSubsystem_h_4171591277(TEXT("/Script/LearnShader"),
	Z_CompiledInDeferFile_FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_Rendering_LearnShaderSubsystem_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_Rendering_LearnShaderSubsystem_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
