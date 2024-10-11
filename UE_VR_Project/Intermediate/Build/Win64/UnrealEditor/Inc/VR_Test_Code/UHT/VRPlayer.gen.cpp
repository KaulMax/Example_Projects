// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VR_Test_Code/VRPlayer.h"
#include "../../Source/Runtime/Engine/Classes/Engine/HitResult.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeVRPlayer() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_APawn();
	ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UWorld_NoRegister();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
	HEADMOUNTEDDISPLAY_API UClass* Z_Construct_UClass_UMotionControllerComponent_NoRegister();
	UPackage* Z_Construct_UPackage__Script_VR_Test_Code();
	VR_TEST_CODE_API UClass* Z_Construct_UClass_AGrabObjectBase_NoRegister();
	VR_TEST_CODE_API UClass* Z_Construct_UClass_AVRPlayer();
	VR_TEST_CODE_API UClass* Z_Construct_UClass_AVRPlayer_NoRegister();
	XRBASE_API UClass* Z_Construct_UClass_UHeadMountedDisplayFunctionLibrary_NoRegister();
// End Cross Module References
	DEFINE_FUNCTION(AVRPlayer::execOnOverlapEnd_GrabRight)
	{
		P_GET_OBJECT(UPrimitiveComponent,Z_Param__overlappedComponent);
		P_GET_OBJECT(AActor,Z_Param__otherActor);
		P_GET_OBJECT(UPrimitiveComponent,Z_Param__otherComp);
		P_GET_PROPERTY(FIntProperty,Z_Param__otherBodyIndex);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnOverlapEnd_GrabRight(Z_Param__overlappedComponent,Z_Param__otherActor,Z_Param__otherComp,Z_Param__otherBodyIndex);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AVRPlayer::execOnOverlapBegin_GrabRight)
	{
		P_GET_OBJECT(UPrimitiveComponent,Z_Param__overlappedComponent);
		P_GET_OBJECT(AActor,Z_Param__otherActor);
		P_GET_OBJECT(UPrimitiveComponent,Z_Param__otherComp);
		P_GET_PROPERTY(FIntProperty,Z_Param__otherBodyIndex);
		P_GET_UBOOL(Z_Param__bFromSweep);
		P_GET_STRUCT_REF(FHitResult,Z_Param_Out__sweepResult);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnOverlapBegin_GrabRight(Z_Param__overlappedComponent,Z_Param__otherActor,Z_Param__otherComp,Z_Param__otherBodyIndex,Z_Param__bFromSweep,Z_Param_Out__sweepResult);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AVRPlayer::execWalk)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Walk();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AVRPlayer::execRelease_RightHand)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Release_RightHand();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AVRPlayer::execGrab_RightHand)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Grab_RightHand();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(AVRPlayer::execSetupVRDepends)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetupVRDepends();
		P_NATIVE_END;
	}
	void AVRPlayer::StaticRegisterNativesAVRPlayer()
	{
		UClass* Class = AVRPlayer::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "Grab_RightHand", &AVRPlayer::execGrab_RightHand },
			{ "OnOverlapBegin_GrabRight", &AVRPlayer::execOnOverlapBegin_GrabRight },
			{ "OnOverlapEnd_GrabRight", &AVRPlayer::execOnOverlapEnd_GrabRight },
			{ "Release_RightHand", &AVRPlayer::execRelease_RightHand },
			{ "SetupVRDepends", &AVRPlayer::execSetupVRDepends },
			{ "Walk", &AVRPlayer::execWalk },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AVRPlayer_Grab_RightHand_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AVRPlayer_Grab_RightHand_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AVRPlayer_Grab_RightHand_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AVRPlayer, nullptr, "Grab_RightHand", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AVRPlayer_Grab_RightHand_Statics::Function_MetaDataParams), Z_Construct_UFunction_AVRPlayer_Grab_RightHand_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_AVRPlayer_Grab_RightHand()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AVRPlayer_Grab_RightHand_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics
	{
		struct VRPlayer_eventOnOverlapBegin_GrabRight_Parms
		{
			UPrimitiveComponent* _overlappedComponent;
			AActor* _otherActor;
			UPrimitiveComponent* _otherComp;
			int32 _otherBodyIndex;
			bool _bFromSweep;
			FHitResult _sweepResult;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp__overlappedComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp__overlappedComponent;
		static const UECodeGen_Private::FObjectPropertyParams NewProp__otherActor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp__otherComp_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp__otherComp;
		static const UECodeGen_Private::FIntPropertyParams NewProp__otherBodyIndex;
		static void NewProp__bFromSweep_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp__bFromSweep;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp__sweepResult_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp__sweepResult;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__overlappedComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__overlappedComponent = { "_overlappedComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRPlayer_eventOnOverlapBegin_GrabRight_Parms, _overlappedComponent), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__overlappedComponent_MetaData), Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__overlappedComponent_MetaData) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__otherActor = { "_otherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRPlayer_eventOnOverlapBegin_GrabRight_Parms, _otherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__otherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__otherComp = { "_otherComp", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRPlayer_eventOnOverlapBegin_GrabRight_Parms, _otherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__otherComp_MetaData), Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__otherComp_MetaData) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__otherBodyIndex = { "_otherBodyIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRPlayer_eventOnOverlapBegin_GrabRight_Parms, _otherBodyIndex), METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__bFromSweep_SetBit(void* Obj)
	{
		((VRPlayer_eventOnOverlapBegin_GrabRight_Parms*)Obj)->_bFromSweep = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__bFromSweep = { "_bFromSweep", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(VRPlayer_eventOnOverlapBegin_GrabRight_Parms), &Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__bFromSweep_SetBit, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__sweepResult_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__sweepResult = { "_sweepResult", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRPlayer_eventOnOverlapBegin_GrabRight_Parms, _sweepResult), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__sweepResult_MetaData), Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__sweepResult_MetaData) }; // 1891709922
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__overlappedComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__otherActor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__otherComp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__otherBodyIndex,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__bFromSweep,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::NewProp__sweepResult,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AVRPlayer, nullptr, "OnOverlapBegin_GrabRight", nullptr, nullptr, Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::PropPointers), sizeof(Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::VRPlayer_eventOnOverlapBegin_GrabRight_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00440401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::Function_MetaDataParams), Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::VRPlayer_eventOnOverlapBegin_GrabRight_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics
	{
		struct VRPlayer_eventOnOverlapEnd_GrabRight_Parms
		{
			UPrimitiveComponent* _overlappedComponent;
			AActor* _otherActor;
			UPrimitiveComponent* _otherComp;
			int32 _otherBodyIndex;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp__overlappedComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp__overlappedComponent;
		static const UECodeGen_Private::FObjectPropertyParams NewProp__otherActor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp__otherComp_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp__otherComp;
		static const UECodeGen_Private::FIntPropertyParams NewProp__otherBodyIndex;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::NewProp__overlappedComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::NewProp__overlappedComponent = { "_overlappedComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRPlayer_eventOnOverlapEnd_GrabRight_Parms, _overlappedComponent), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::NewProp__overlappedComponent_MetaData), Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::NewProp__overlappedComponent_MetaData) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::NewProp__otherActor = { "_otherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRPlayer_eventOnOverlapEnd_GrabRight_Parms, _otherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::NewProp__otherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::NewProp__otherComp = { "_otherComp", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRPlayer_eventOnOverlapEnd_GrabRight_Parms, _otherComp), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::NewProp__otherComp_MetaData), Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::NewProp__otherComp_MetaData) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::NewProp__otherBodyIndex = { "_otherBodyIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VRPlayer_eventOnOverlapEnd_GrabRight_Parms, _otherBodyIndex), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::NewProp__overlappedComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::NewProp__otherActor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::NewProp__otherComp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::NewProp__otherBodyIndex,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AVRPlayer, nullptr, "OnOverlapEnd_GrabRight", nullptr, nullptr, Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::PropPointers), sizeof(Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::VRPlayer_eventOnOverlapEnd_GrabRight_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::Function_MetaDataParams), Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::VRPlayer_eventOnOverlapEnd_GrabRight_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AVRPlayer_Release_RightHand_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AVRPlayer_Release_RightHand_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AVRPlayer_Release_RightHand_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AVRPlayer, nullptr, "Release_RightHand", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AVRPlayer_Release_RightHand_Statics::Function_MetaDataParams), Z_Construct_UFunction_AVRPlayer_Release_RightHand_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_AVRPlayer_Release_RightHand()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AVRPlayer_Release_RightHand_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AVRPlayer_SetupVRDepends_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AVRPlayer_SetupVRDepends_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AVRPlayer_SetupVRDepends_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AVRPlayer, nullptr, "SetupVRDepends", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AVRPlayer_SetupVRDepends_Statics::Function_MetaDataParams), Z_Construct_UFunction_AVRPlayer_SetupVRDepends_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_AVRPlayer_SetupVRDepends()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AVRPlayer_SetupVRDepends_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AVRPlayer_Walk_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AVRPlayer_Walk_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AVRPlayer_Walk_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AVRPlayer, nullptr, "Walk", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AVRPlayer_Walk_Statics::Function_MetaDataParams), Z_Construct_UFunction_AVRPlayer_Walk_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_AVRPlayer_Walk()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AVRPlayer_Walk_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AVRPlayer);
	UClass* Z_Construct_UClass_AVRPlayer_NoRegister()
	{
		return AVRPlayer::StaticClass();
	}
	struct Z_Construct_UClass_AVRPlayer_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_defaultMappingContext_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_defaultMappingContext;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_grabAction_RightHand_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_grabAction_RightHand;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_firstPersonCameraComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_firstPersonCameraComponent;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_world_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_world;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_VRRoot_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_VRRoot;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_motionController_RightHand_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_motionController_RightHand;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_motionController_LeftHand_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_motionController_LeftHand;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_mesh_RightHand_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_mesh_RightHand;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_mesh_LeftHand_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_mesh_LeftHand;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_currOverlapActor_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_currOverlapActor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_currGrabActor_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_currGrabActor;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_displayLib_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_displayLib;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AVRPlayer_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APawn,
		(UObject* (*)())Z_Construct_UPackage__Script_VR_Test_Code,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AVRPlayer_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_AVRPlayer_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AVRPlayer_Grab_RightHand, "Grab_RightHand" }, // 524225525
		{ &Z_Construct_UFunction_AVRPlayer_OnOverlapBegin_GrabRight, "OnOverlapBegin_GrabRight" }, // 814672899
		{ &Z_Construct_UFunction_AVRPlayer_OnOverlapEnd_GrabRight, "OnOverlapEnd_GrabRight" }, // 1543981950
		{ &Z_Construct_UFunction_AVRPlayer_Release_RightHand, "Release_RightHand" }, // 3726853047
		{ &Z_Construct_UFunction_AVRPlayer_SetupVRDepends, "SetupVRDepends" }, // 1005877808
		{ &Z_Construct_UFunction_AVRPlayer_Walk, "Walk" }, // 3603699314
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AVRPlayer_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVRPlayer_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "VRPlayer.h" },
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVRPlayer_Statics::NewProp_defaultMappingContext_MetaData[] = {
		{ "AllowPrivateAccess", "" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AVRPlayer_Statics::NewProp_defaultMappingContext = { "defaultMappingContext", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AVRPlayer, defaultMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AVRPlayer_Statics::NewProp_defaultMappingContext_MetaData), Z_Construct_UClass_AVRPlayer_Statics::NewProp_defaultMappingContext_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVRPlayer_Statics::NewProp_grabAction_RightHand_MetaData[] = {
		{ "AllowPrivateAccess", "" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AVRPlayer_Statics::NewProp_grabAction_RightHand = { "grabAction_RightHand", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AVRPlayer, grabAction_RightHand), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AVRPlayer_Statics::NewProp_grabAction_RightHand_MetaData), Z_Construct_UClass_AVRPlayer_Statics::NewProp_grabAction_RightHand_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVRPlayer_Statics::NewProp_firstPersonCameraComponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AVRPlayer_Statics::NewProp_firstPersonCameraComponent = { "firstPersonCameraComponent", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AVRPlayer, firstPersonCameraComponent), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AVRPlayer_Statics::NewProp_firstPersonCameraComponent_MetaData), Z_Construct_UClass_AVRPlayer_Statics::NewProp_firstPersonCameraComponent_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVRPlayer_Statics::NewProp_world_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AVRPlayer_Statics::NewProp_world = { "world", nullptr, (EPropertyFlags)0x0040000000020015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AVRPlayer, world), Z_Construct_UClass_UWorld_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AVRPlayer_Statics::NewProp_world_MetaData), Z_Construct_UClass_AVRPlayer_Statics::NewProp_world_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVRPlayer_Statics::NewProp_VRRoot_MetaData[] = {
		{ "AllowPrivateAccess", "" },
		{ "Category", "VR" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AVRPlayer_Statics::NewProp_VRRoot = { "VRRoot", nullptr, (EPropertyFlags)0x004000000008001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AVRPlayer, VRRoot), Z_Construct_UClass_USceneComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AVRPlayer_Statics::NewProp_VRRoot_MetaData), Z_Construct_UClass_AVRPlayer_Statics::NewProp_VRRoot_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVRPlayer_Statics::NewProp_motionController_RightHand_MetaData[] = {
		{ "AllowPrivateAccess", "" },
		{ "Category", "VR" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AVRPlayer_Statics::NewProp_motionController_RightHand = { "motionController_RightHand", nullptr, (EPropertyFlags)0x004000000008001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AVRPlayer, motionController_RightHand), Z_Construct_UClass_UMotionControllerComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AVRPlayer_Statics::NewProp_motionController_RightHand_MetaData), Z_Construct_UClass_AVRPlayer_Statics::NewProp_motionController_RightHand_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVRPlayer_Statics::NewProp_motionController_LeftHand_MetaData[] = {
		{ "AllowPrivateAccess", "" },
		{ "Category", "VR" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AVRPlayer_Statics::NewProp_motionController_LeftHand = { "motionController_LeftHand", nullptr, (EPropertyFlags)0x004000000008001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AVRPlayer, motionController_LeftHand), Z_Construct_UClass_UMotionControllerComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AVRPlayer_Statics::NewProp_motionController_LeftHand_MetaData), Z_Construct_UClass_AVRPlayer_Statics::NewProp_motionController_LeftHand_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVRPlayer_Statics::NewProp_mesh_RightHand_MetaData[] = {
		{ "AllowPrivateAccess", "" },
		{ "Category", "VR" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AVRPlayer_Statics::NewProp_mesh_RightHand = { "mesh_RightHand", nullptr, (EPropertyFlags)0x004000000008001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AVRPlayer, mesh_RightHand), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AVRPlayer_Statics::NewProp_mesh_RightHand_MetaData), Z_Construct_UClass_AVRPlayer_Statics::NewProp_mesh_RightHand_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVRPlayer_Statics::NewProp_mesh_LeftHand_MetaData[] = {
		{ "AllowPrivateAccess", "" },
		{ "Category", "VR" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AVRPlayer_Statics::NewProp_mesh_LeftHand = { "mesh_LeftHand", nullptr, (EPropertyFlags)0x004000000008001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AVRPlayer, mesh_LeftHand), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AVRPlayer_Statics::NewProp_mesh_LeftHand_MetaData), Z_Construct_UClass_AVRPlayer_Statics::NewProp_mesh_LeftHand_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVRPlayer_Statics::NewProp_currOverlapActor_MetaData[] = {
		{ "AllowPrivateAccess", "" },
		{ "Category", "VRPlayer" },
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AVRPlayer_Statics::NewProp_currOverlapActor = { "currOverlapActor", nullptr, (EPropertyFlags)0x0040000000020001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AVRPlayer, currOverlapActor), Z_Construct_UClass_AGrabObjectBase_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AVRPlayer_Statics::NewProp_currOverlapActor_MetaData), Z_Construct_UClass_AVRPlayer_Statics::NewProp_currOverlapActor_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVRPlayer_Statics::NewProp_currGrabActor_MetaData[] = {
		{ "AllowPrivateAccess", "" },
		{ "Category", "VRPlayer" },
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AVRPlayer_Statics::NewProp_currGrabActor = { "currGrabActor", nullptr, (EPropertyFlags)0x0040000000020001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AVRPlayer, currGrabActor), Z_Construct_UClass_AGrabObjectBase_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AVRPlayer_Statics::NewProp_currGrabActor_MetaData), Z_Construct_UClass_AVRPlayer_Statics::NewProp_currGrabActor_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVRPlayer_Statics::NewProp_displayLib_MetaData[] = {
		{ "ModuleRelativePath", "VRPlayer.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AVRPlayer_Statics::NewProp_displayLib = { "displayLib", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AVRPlayer, displayLib), Z_Construct_UClass_UHeadMountedDisplayFunctionLibrary_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AVRPlayer_Statics::NewProp_displayLib_MetaData), Z_Construct_UClass_AVRPlayer_Statics::NewProp_displayLib_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AVRPlayer_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AVRPlayer_Statics::NewProp_defaultMappingContext,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AVRPlayer_Statics::NewProp_grabAction_RightHand,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AVRPlayer_Statics::NewProp_firstPersonCameraComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AVRPlayer_Statics::NewProp_world,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AVRPlayer_Statics::NewProp_VRRoot,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AVRPlayer_Statics::NewProp_motionController_RightHand,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AVRPlayer_Statics::NewProp_motionController_LeftHand,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AVRPlayer_Statics::NewProp_mesh_RightHand,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AVRPlayer_Statics::NewProp_mesh_LeftHand,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AVRPlayer_Statics::NewProp_currOverlapActor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AVRPlayer_Statics::NewProp_currGrabActor,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AVRPlayer_Statics::NewProp_displayLib,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AVRPlayer_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AVRPlayer>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AVRPlayer_Statics::ClassParams = {
		&AVRPlayer::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AVRPlayer_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AVRPlayer_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AVRPlayer_Statics::Class_MetaDataParams), Z_Construct_UClass_AVRPlayer_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AVRPlayer_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AVRPlayer()
	{
		if (!Z_Registration_Info_UClass_AVRPlayer.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AVRPlayer.OuterSingleton, Z_Construct_UClass_AVRPlayer_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AVRPlayer.OuterSingleton;
	}
	template<> VR_TEST_CODE_API UClass* StaticClass<AVRPlayer>()
	{
		return AVRPlayer::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AVRPlayer);
	AVRPlayer::~AVRPlayer() {}
	struct Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AVRPlayer, AVRPlayer::StaticClass, TEXT("AVRPlayer"), &Z_Registration_Info_UClass_AVRPlayer, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AVRPlayer), 4077662933U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_3190945557(TEXT("/Script/VR_Test_Code"),
		Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_VRPlayer_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
