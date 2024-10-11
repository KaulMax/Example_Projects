// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GrabComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UMotionControllerComponent;
#ifdef VR_TEST_CODE_GrabComponent_generated_h
#error "GrabComponent.generated.h already included, missing '#pragma once' in GrabComponent.h"
#endif
#define VR_TEST_CODE_GrabComponent_generated_h

#define FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_23_SPARSE_DATA
#define FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_23_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_23_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execTryReleaseObject); \
	DECLARE_FUNCTION(execTryGrabObject); \
	DECLARE_FUNCTION(execInitGrabComponent);


#define FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_23_ACCESSORS
#define FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_23_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGrabComponent(); \
	friend struct Z_Construct_UClass_UGrabComponent_Statics; \
public: \
	DECLARE_CLASS(UGrabComponent, USceneComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/VR_Test_Code"), NO_API) \
	DECLARE_SERIALIZER(UGrabComponent)


#define FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_23_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGrabComponent(UGrabComponent&&); \
	NO_API UGrabComponent(const UGrabComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGrabComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGrabComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UGrabComponent) \
	NO_API virtual ~UGrabComponent();


#define FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_20_PROLOG
#define FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_23_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_23_SPARSE_DATA \
	FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_23_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_23_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_23_ACCESSORS \
	FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_23_INCLASS_NO_PURE_DECLS \
	FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_23_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> VR_TEST_CODE_API UClass* StaticClass<class UGrabComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h


#define FOREACH_ENUM_EGRABTYPE(op) \
	op(EGrabType::GT_DEFAULT) \
	op(EGrabType::GT_Free) \
	op(EGrabType::GT_Snap) \
	op(EGrabType::GT_ENTRY_AMOUNT) 

enum class EGrabType;
template<> struct TIsUEnumClass<EGrabType> { enum { Value = true }; };
template<> VR_TEST_CODE_API UEnum* StaticEnum<EGrabType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
