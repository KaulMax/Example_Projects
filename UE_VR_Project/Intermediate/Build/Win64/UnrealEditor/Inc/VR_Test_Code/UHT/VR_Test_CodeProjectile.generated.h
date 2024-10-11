// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "VR_Test_CodeProjectile.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UPrimitiveComponent;
struct FHitResult;
#ifdef VR_TEST_CODE_VR_Test_CodeProjectile_generated_h
#error "VR_Test_CodeProjectile.generated.h already included, missing '#pragma once' in VR_Test_CodeProjectile.h"
#endif
#define VR_TEST_CODE_VR_Test_CodeProjectile_generated_h

#define FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeProjectile_h_15_SPARSE_DATA
#define FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeProjectile_h_15_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeProjectile_h_15_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeProjectile_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnHit);


#define FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeProjectile_h_15_ACCESSORS
#define FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeProjectile_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAVR_Test_CodeProjectile(); \
	friend struct Z_Construct_UClass_AVR_Test_CodeProjectile_Statics; \
public: \
	DECLARE_CLASS(AVR_Test_CodeProjectile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/VR_Test_Code"), NO_API) \
	DECLARE_SERIALIZER(AVR_Test_CodeProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeProjectile_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AVR_Test_CodeProjectile(AVR_Test_CodeProjectile&&); \
	NO_API AVR_Test_CodeProjectile(const AVR_Test_CodeProjectile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AVR_Test_CodeProjectile); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AVR_Test_CodeProjectile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AVR_Test_CodeProjectile) \
	NO_API virtual ~AVR_Test_CodeProjectile();


#define FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeProjectile_h_12_PROLOG
#define FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeProjectile_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeProjectile_h_15_SPARSE_DATA \
	FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeProjectile_h_15_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeProjectile_h_15_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeProjectile_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeProjectile_h_15_ACCESSORS \
	FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeProjectile_h_15_INCLASS_NO_PURE_DECLS \
	FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeProjectile_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> VR_TEST_CODE_API UClass* StaticClass<class AVR_Test_CodeProjectile>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeProjectile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
