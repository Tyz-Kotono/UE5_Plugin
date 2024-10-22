// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LearnShader/RenderTarget/RTLibrary.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRTLibrary() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
ENGINE_API UClass* Z_Construct_UClass_UTextureRenderTarget2D_NoRegister();
LEARNSHADER_API UClass* Z_Construct_UClass_URTLibrary();
LEARNSHADER_API UClass* Z_Construct_UClass_URTLibrary_NoRegister();
UPackage* Z_Construct_UPackage__Script_LearnShader();
// End Cross Module References

// Begin Class URTLibrary Function DrawRenderTarget_Function
struct Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function_Statics
{
	struct RTLibrary_eventDrawRenderTarget_Function_Parms
	{
		UTextureRenderTarget2D* OutRenderTarget;
		FLinearColor Color;
		const UObject* WorldActor;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Render Liberay" },
		{ "ModuleRelativePath", "RenderTarget/RTLibrary.h" },
		{ "WorldContext", "WorldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Color_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldActor_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OutRenderTarget;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Color;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldActor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function_Statics::NewProp_OutRenderTarget = { "OutRenderTarget", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RTLibrary_eventDrawRenderTarget_Function_Parms, OutRenderTarget), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function_Statics::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RTLibrary_eventDrawRenderTarget_Function_Parms, Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Color_MetaData), NewProp_Color_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function_Statics::NewProp_WorldActor = { "WorldActor", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(RTLibrary_eventDrawRenderTarget_Function_Parms, WorldActor), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldActor_MetaData), NewProp_WorldActor_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function_Statics::NewProp_OutRenderTarget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function_Statics::NewProp_Color,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function_Statics::NewProp_WorldActor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URTLibrary, nullptr, "DrawRenderTarget_Function", nullptr, nullptr, Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function_Statics::PropPointers), sizeof(Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function_Statics::RTLibrary_eventDrawRenderTarget_Function_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04842401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function_Statics::Function_MetaDataParams), Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function_Statics::RTLibrary_eventDrawRenderTarget_Function_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(URTLibrary::execDrawRenderTarget_Function)
{
	P_GET_OBJECT(UTextureRenderTarget2D,Z_Param_OutRenderTarget);
	P_GET_STRUCT(FLinearColor,Z_Param_Color);
	P_GET_OBJECT(UObject,Z_Param_WorldActor);
	P_FINISH;
	P_NATIVE_BEGIN;
	URTLibrary::DrawRenderTarget_Function(Z_Param_OutRenderTarget,Z_Param_Color,Z_Param_WorldActor);
	P_NATIVE_END;
}
// End Class URTLibrary Function DrawRenderTarget_Function

// Begin Class URTLibrary
void URTLibrary::StaticRegisterNativesURTLibrary()
{
	UClass* Class = URTLibrary::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "DrawRenderTarget_Function", &URTLibrary::execDrawRenderTarget_Function },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(URTLibrary);
UClass* Z_Construct_UClass_URTLibrary_NoRegister()
{
	return URTLibrary::StaticClass();
}
struct Z_Construct_UClass_URTLibrary_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "RenderTarget/RTLibrary.h" },
		{ "ModuleRelativePath", "RenderTarget/RTLibrary.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_URTLibrary_DrawRenderTarget_Function, "DrawRenderTarget_Function" }, // 1826890628
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URTLibrary>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_URTLibrary_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
	(UObject* (*)())Z_Construct_UPackage__Script_LearnShader,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URTLibrary_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_URTLibrary_Statics::ClassParams = {
	&URTLibrary::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URTLibrary_Statics::Class_MetaDataParams), Z_Construct_UClass_URTLibrary_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_URTLibrary()
{
	if (!Z_Registration_Info_UClass_URTLibrary.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_URTLibrary.OuterSingleton, Z_Construct_UClass_URTLibrary_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_URTLibrary.OuterSingleton;
}
template<> LEARNSHADER_API UClass* StaticClass<URTLibrary>()
{
	return URTLibrary::StaticClass();
}
URTLibrary::URTLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(URTLibrary);
URTLibrary::~URTLibrary() {}
// End Class URTLibrary

// Begin Registration
struct Z_CompiledInDeferFile_FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_RenderTarget_RTLibrary_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_URTLibrary, URTLibrary::StaticClass, TEXT("URTLibrary"), &Z_Registration_Info_UClass_URTLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URTLibrary), 1335304655U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_RenderTarget_RTLibrary_h_4159381926(TEXT("/Script/LearnShader"),
	Z_CompiledInDeferFile_FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_RenderTarget_RTLibrary_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_RenderTarget_RTLibrary_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
