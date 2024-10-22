// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "RenderTarget/RTLibrary.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
class UTextureRenderTarget2D;
struct FLinearColor;
#ifdef LEARNSHADER_RTLibrary_generated_h
#error "RTLibrary.generated.h already included, missing '#pragma once' in RTLibrary.h"
#endif
#define LEARNSHADER_RTLibrary_generated_h

#define FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_RenderTarget_RTLibrary_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDrawRenderTarget_Function);


#define FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_RenderTarget_RTLibrary_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesURTLibrary(); \
	friend struct Z_Construct_UClass_URTLibrary_Statics; \
public: \
	DECLARE_CLASS(URTLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/LearnShader"), NO_API) \
	DECLARE_SERIALIZER(URTLibrary)


#define FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_RenderTarget_RTLibrary_h_13_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API URTLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	URTLibrary(URTLibrary&&); \
	URTLibrary(const URTLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, URTLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(URTLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(URTLibrary) \
	NO_API virtual ~URTLibrary();


#define FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_RenderTarget_RTLibrary_h_10_PROLOG
#define FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_RenderTarget_RTLibrary_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_RenderTarget_RTLibrary_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_RenderTarget_RTLibrary_h_13_INCLASS_NO_PURE_DECLS \
	FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_RenderTarget_RTLibrary_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LEARNSHADER_API UClass* StaticClass<class URTLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Render_SUE54Render_Plugins_LearnShader_Source_LearnShader_RenderTarget_RTLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
