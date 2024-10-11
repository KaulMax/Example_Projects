// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "VRPlayer.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UPrimitiveComponent;
struct FHitResult;
#ifdef VR_TEST_CODE_VRPlayer_generated_h
#error "VRPlayer.generated.h already included, missing '#pragma once' in VRPlayer.h"
#endif
#define VR_TEST_CODE_VRPlayer_generated_h

#define FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_12_SPARSE_DATA
#define FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_12_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_12_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnOverlapEnd_GrabRight); \
	DECLARE_FUNCTION(execOnOverlapBegin_GrabRight); \
	DECLARE_FUNCTION(execWalk); \
	DECLARE_FUNCTION(execRelease_RightHand); \
	DECLARE_FUNCTION(execGrab_RightHand); \
	DECLARE_FUNCTION(execSetupVRDepends);


#define FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_12_ACCESSORS
#define FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAVRPlayer(); \
	friend struct Z_Construct_UClass_AVRPlayer_Statics; \
public: \
	DECLARE_CLASS(AVRPlayer, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/VR_Test_Code"), NO_API) \
	DECLARE_SERIALIZER(AVRPlayer)


#define FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AVRPlayer(AVRPlayer&&); \
	NO_API AVRPlayer(const AVRPlayer&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AVRPlayer); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AVRPlayer); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AVRPlayer) \
	NO_API virtual ~AVRPlayer();


#define FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_9_PROLOG
#define FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_12_SPARSE_DATA \
	FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_12_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_12_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_12_ACCESSORS \
	FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_12_INCLASS_NO_PURE_DECLS \
	FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> VR_TEST_CODE_API UClass* StaticClass<class AVRPlayer>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
