// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VR_Test_Code/GrabComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGrabComponent() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
	HEADMOUNTEDDISPLAY_API UClass* Z_Construct_UClass_UMotionControllerComponent_NoRegister();
	UPackage* Z_Construct_UPackage__Script_VR_Test_Code();
	VR_TEST_CODE_API UClass* Z_Construct_UClass_UGrabComponent();
	VR_TEST_CODE_API UClass* Z_Construct_UClass_UGrabComponent_NoRegister();
	VR_TEST_CODE_API UEnum* Z_Construct_UEnum_VR_Test_Code_EGrabType();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_EGrabType;
	static UEnum* EGrabType_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_EGrabType.OuterSingleton)
		{
			Z_Registration_Info_UEnum_EGrabType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_VR_Test_Code_EGrabType, (UObject*)Z_Construct_UPackage__Script_VR_Test_Code(), TEXT("EGrabType"));
		}
		return Z_Registration_Info_UEnum_EGrabType.OuterSingleton;
	}
	template<> VR_TEST_CODE_API UEnum* StaticEnum<EGrabType>()
	{
		return EGrabType_StaticEnum();
	}
	struct Z_Construct_UEnum_VR_Test_Code_EGrabType_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_VR_Test_Code_EGrabType_Statics::Enumerators[] = {
		{ "EGrabType::GT_DEFAULT", (int64)EGrabType::GT_DEFAULT },
		{ "EGrabType::GT_Free", (int64)EGrabType::GT_Free },
		{ "EGrabType::GT_Snap", (int64)EGrabType::GT_Snap },
		{ "EGrabType::GT_ENTRY_AMOUNT", (int64)EGrabType::GT_ENTRY_AMOUNT },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_VR_Test_Code_EGrabType_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "GT_DEFAULT.Name", "EGrabType::GT_DEFAULT" },
		{ "GT_ENTRY_AMOUNT.Name", "EGrabType::GT_ENTRY_AMOUNT" },
		{ "GT_Free.Name", "EGrabType::GT_Free" },
		{ "GT_Snap.Name", "EGrabType::GT_Snap" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "GrabComponent.h" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_VR_Test_Code_EGrabType_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_VR_Test_Code,
		nullptr,
		"EGrabType",
		"EGrabType",
		Z_Construct_UEnum_VR_Test_Code_EGrabType_Statics::Enumerators,
		RF_Public|RF_Transient|RF_MarkAsNative,
		UE_ARRAY_COUNT(Z_Construct_UEnum_VR_Test_Code_EGrabType_Statics::Enumerators),
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_VR_Test_Code_EGrabType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_VR_Test_Code_EGrabType_Statics::Enum_MetaDataParams)
	};
	UEnum* Z_Construct_UEnum_VR_Test_Code_EGrabType()
	{
		if (!Z_Registration_Info_UEnum_EGrabType.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EGrabType.InnerSingleton, Z_Construct_UEnum_VR_Test_Code_EGrabType_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_EGrabType.InnerSingleton;
	}
	DEFINE_FUNCTION(UGrabComponent::execTryReleaseObject)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->TryReleaseObject();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGrabComponent::execTryGrabObject)
	{
		P_GET_OBJECT(AActor,Z_Param__grabHolder);
		P_GET_OBJECT(UMotionControllerComponent,Z_Param__grabController);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->TryGrabObject(Z_Param__grabHolder,Z_Param__grabController);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGrabComponent::execInitGrabComponent)
	{
		P_GET_OBJECT(AActor,Z_Param__compParent);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->InitGrabComponent(Z_Param__compParent);
		P_NATIVE_END;
	}
	void UGrabComponent::StaticRegisterNativesUGrabComponent()
	{
		UClass* Class = UGrabComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "InitGrabComponent", &UGrabComponent::execInitGrabComponent },
			{ "TryGrabObject", &UGrabComponent::execTryGrabObject },
			{ "TryReleaseObject", &UGrabComponent::execTryReleaseObject },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGrabComponent_InitGrabComponent_Statics
	{
		struct GrabComponent_eventInitGrabComponent_Parms
		{
			AActor* _compParent;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp__compParent;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGrabComponent_InitGrabComponent_Statics::NewProp__compParent = { "_compParent", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GrabComponent_eventInitGrabComponent_Parms, _compParent), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGrabComponent_InitGrabComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGrabComponent_InitGrabComponent_Statics::NewProp__compParent,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGrabComponent_InitGrabComponent_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "GrabComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGrabComponent_InitGrabComponent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGrabComponent, nullptr, "InitGrabComponent", nullptr, nullptr, Z_Construct_UFunction_UGrabComponent_InitGrabComponent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGrabComponent_InitGrabComponent_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGrabComponent_InitGrabComponent_Statics::GrabComponent_eventInitGrabComponent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGrabComponent_InitGrabComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGrabComponent_InitGrabComponent_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGrabComponent_InitGrabComponent_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UGrabComponent_InitGrabComponent_Statics::GrabComponent_eventInitGrabComponent_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UGrabComponent_InitGrabComponent()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGrabComponent_InitGrabComponent_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics
	{
		struct GrabComponent_eventTryGrabObject_Parms
		{
			AActor* _grabHolder;
			UMotionControllerComponent* _grabController;
			bool ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp__grabHolder;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp__grabController_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp__grabController;
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::NewProp__grabHolder = { "_grabHolder", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GrabComponent_eventTryGrabObject_Parms, _grabHolder), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::NewProp__grabController_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::NewProp__grabController = { "_grabController", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GrabComponent_eventTryGrabObject_Parms, _grabController), Z_Construct_UClass_UMotionControllerComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::NewProp__grabController_MetaData), Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::NewProp__grabController_MetaData) };
	void Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((GrabComponent_eventTryGrabObject_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GrabComponent_eventTryGrabObject_Parms), &Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::NewProp__grabHolder,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::NewProp__grabController,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "GrabComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGrabComponent, nullptr, "TryGrabObject", nullptr, nullptr, Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::GrabComponent_eventTryGrabObject_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::GrabComponent_eventTryGrabObject_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UGrabComponent_TryGrabObject()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGrabComponent_TryGrabObject_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGrabComponent_TryReleaseObject_Statics
	{
		struct GrabComponent_eventTryReleaseObject_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UGrabComponent_TryReleaseObject_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((GrabComponent_eventTryReleaseObject_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGrabComponent_TryReleaseObject_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GrabComponent_eventTryReleaseObject_Parms), &Z_Construct_UFunction_UGrabComponent_TryReleaseObject_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGrabComponent_TryReleaseObject_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGrabComponent_TryReleaseObject_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGrabComponent_TryReleaseObject_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "GrabComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGrabComponent_TryReleaseObject_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGrabComponent, nullptr, "TryReleaseObject", nullptr, nullptr, Z_Construct_UFunction_UGrabComponent_TryReleaseObject_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGrabComponent_TryReleaseObject_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGrabComponent_TryReleaseObject_Statics::GrabComponent_eventTryReleaseObject_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGrabComponent_TryReleaseObject_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGrabComponent_TryReleaseObject_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGrabComponent_TryReleaseObject_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UGrabComponent_TryReleaseObject_Statics::GrabComponent_eventTryReleaseObject_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UGrabComponent_TryReleaseObject()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGrabComponent_TryReleaseObject_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGrabComponent);
	UClass* Z_Construct_UClass_UGrabComponent_NoRegister()
	{
		return UGrabComponent::StaticClass();
	}
	struct Z_Construct_UClass_UGrabComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_grabType_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_grabType_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_grabType;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bIsBeingHeld_MetaData[];
#endif
		static void NewProp_bIsBeingHeld_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsBeingHeld;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_currHolder_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_currHolder;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_currController_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_currController;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_compParent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_compParent;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGrabComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USceneComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_VR_Test_Code,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGrabComponent_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UGrabComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UGrabComponent_InitGrabComponent, "InitGrabComponent" }, // 2850216583
		{ &Z_Construct_UFunction_UGrabComponent_TryGrabObject, "TryGrabObject" }, // 502361286
		{ &Z_Construct_UFunction_UGrabComponent_TryReleaseObject, "TryReleaseObject" }, // 3979451082
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGrabComponent_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGrabComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "GrabComponent.h" },
		{ "ModuleRelativePath", "GrabComponent.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGrabComponent_Statics::NewProp_grabType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGrabComponent_Statics::NewProp_grabType_MetaData[] = {
		{ "AllowPrivateAccess", "" },
		{ "Category", "ObjectInfo" },
		{ "ModuleRelativePath", "GrabComponent.h" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UGrabComponent_Statics::NewProp_grabType = { "grabType", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGrabComponent, grabType), Z_Construct_UEnum_VR_Test_Code_EGrabType, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGrabComponent_Statics::NewProp_grabType_MetaData), Z_Construct_UClass_UGrabComponent_Statics::NewProp_grabType_MetaData) }; // 3816158106
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGrabComponent_Statics::NewProp_bIsBeingHeld_MetaData[] = {
		{ "AllowPrivateAccess", "" },
		{ "Category", "ObjectInfo" },
		{ "ModuleRelativePath", "GrabComponent.h" },
	};
#endif
	void Z_Construct_UClass_UGrabComponent_Statics::NewProp_bIsBeingHeld_SetBit(void* Obj)
	{
		((UGrabComponent*)Obj)->bIsBeingHeld = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UGrabComponent_Statics::NewProp_bIsBeingHeld = { "bIsBeingHeld", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UGrabComponent), &Z_Construct_UClass_UGrabComponent_Statics::NewProp_bIsBeingHeld_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGrabComponent_Statics::NewProp_bIsBeingHeld_MetaData), Z_Construct_UClass_UGrabComponent_Statics::NewProp_bIsBeingHeld_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGrabComponent_Statics::NewProp_currHolder_MetaData[] = {
		{ "AllowPrivateAccess", "" },
		{ "Category", "GrabComponent" },
		{ "ModuleRelativePath", "GrabComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGrabComponent_Statics::NewProp_currHolder = { "currHolder", nullptr, (EPropertyFlags)0x0040000000020001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGrabComponent, currHolder), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGrabComponent_Statics::NewProp_currHolder_MetaData), Z_Construct_UClass_UGrabComponent_Statics::NewProp_currHolder_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGrabComponent_Statics::NewProp_currController_MetaData[] = {
		{ "AllowPrivateAccess", "" },
		{ "Category", "GrabComponent" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "GrabComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGrabComponent_Statics::NewProp_currController = { "currController", nullptr, (EPropertyFlags)0x00400000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGrabComponent, currController), Z_Construct_UClass_UMotionControllerComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGrabComponent_Statics::NewProp_currController_MetaData), Z_Construct_UClass_UGrabComponent_Statics::NewProp_currController_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGrabComponent_Statics::NewProp_compParent_MetaData[] = {
		{ "AllowPrivateAccess", "" },
		{ "Category", "GrabComponent" },
		{ "ModuleRelativePath", "GrabComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGrabComponent_Statics::NewProp_compParent = { "compParent", nullptr, (EPropertyFlags)0x0040000000020001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGrabComponent, compParent), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGrabComponent_Statics::NewProp_compParent_MetaData), Z_Construct_UClass_UGrabComponent_Statics::NewProp_compParent_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGrabComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrabComponent_Statics::NewProp_grabType_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrabComponent_Statics::NewProp_grabType,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrabComponent_Statics::NewProp_bIsBeingHeld,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrabComponent_Statics::NewProp_currHolder,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrabComponent_Statics::NewProp_currController,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGrabComponent_Statics::NewProp_compParent,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGrabComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGrabComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UGrabComponent_Statics::ClassParams = {
		&UGrabComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UGrabComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UGrabComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGrabComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UGrabComponent_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGrabComponent_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UGrabComponent()
	{
		if (!Z_Registration_Info_UClass_UGrabComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGrabComponent.OuterSingleton, Z_Construct_UClass_UGrabComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UGrabComponent.OuterSingleton;
	}
	template<> VR_TEST_CODE_API UClass* StaticClass<UGrabComponent>()
	{
		return UGrabComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGrabComponent);
	UGrabComponent::~UGrabComponent() {}
	struct Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_Statics::EnumInfo[] = {
		{ EGrabType_StaticEnum, TEXT("EGrabType"), &Z_Registration_Info_UEnum_EGrabType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3816158106U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UGrabComponent, UGrabComponent::StaticClass, TEXT("UGrabComponent"), &Z_Registration_Info_UClass_UGrabComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGrabComponent), 2579957085U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_935483301(TEXT("/Script/VR_Test_Code"),
		Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_Statics::ClassInfo),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_GrabComponent_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
