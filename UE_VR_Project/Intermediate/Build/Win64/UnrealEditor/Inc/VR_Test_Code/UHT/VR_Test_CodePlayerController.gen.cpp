// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VR_Test_Code/VR_Test_CodePlayerController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeVR_Test_CodePlayerController() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
	UPackage* Z_Construct_UPackage__Script_VR_Test_Code();
	VR_TEST_CODE_API UClass* Z_Construct_UClass_AVR_Test_CodePlayerController();
	VR_TEST_CODE_API UClass* Z_Construct_UClass_AVR_Test_CodePlayerController_NoRegister();
// End Cross Module References
	void AVR_Test_CodePlayerController::StaticRegisterNativesAVR_Test_CodePlayerController()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AVR_Test_CodePlayerController);
	UClass* Z_Construct_UClass_AVR_Test_CodePlayerController_NoRegister()
	{
		return AVR_Test_CodePlayerController::StaticClass();
	}
	struct Z_Construct_UClass_AVR_Test_CodePlayerController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InputMappingContext_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_InputMappingContext;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AVR_Test_CodePlayerController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_VR_Test_Code,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AVR_Test_CodePlayerController_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVR_Test_CodePlayerController_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *\n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "VR_Test_CodePlayerController.h" },
		{ "ModuleRelativePath", "VR_Test_CodePlayerController.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVR_Test_CodePlayerController_Statics::NewProp_InputMappingContext_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input Mapping Context to be used for player input */" },
#endif
		{ "ModuleRelativePath", "VR_Test_CodePlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Mapping Context to be used for player input" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AVR_Test_CodePlayerController_Statics::NewProp_InputMappingContext = { "InputMappingContext", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AVR_Test_CodePlayerController, InputMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AVR_Test_CodePlayerController_Statics::NewProp_InputMappingContext_MetaData), Z_Construct_UClass_AVR_Test_CodePlayerController_Statics::NewProp_InputMappingContext_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AVR_Test_CodePlayerController_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AVR_Test_CodePlayerController_Statics::NewProp_InputMappingContext,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AVR_Test_CodePlayerController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AVR_Test_CodePlayerController>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AVR_Test_CodePlayerController_Statics::ClassParams = {
		&AVR_Test_CodePlayerController::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AVR_Test_CodePlayerController_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AVR_Test_CodePlayerController_Statics::PropPointers),
		0,
		0x009002A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AVR_Test_CodePlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_AVR_Test_CodePlayerController_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AVR_Test_CodePlayerController_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AVR_Test_CodePlayerController()
	{
		if (!Z_Registration_Info_UClass_AVR_Test_CodePlayerController.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AVR_Test_CodePlayerController.OuterSingleton, Z_Construct_UClass_AVR_Test_CodePlayerController_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AVR_Test_CodePlayerController.OuterSingleton;
	}
	template<> VR_TEST_CODE_API UClass* StaticClass<AVR_Test_CodePlayerController>()
	{
		return AVR_Test_CodePlayerController::StaticClass();
	}
	AVR_Test_CodePlayerController::AVR_Test_CodePlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AVR_Test_CodePlayerController);
	AVR_Test_CodePlayerController::~AVR_Test_CodePlayerController() {}
	struct Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodePlayerController_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodePlayerController_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AVR_Test_CodePlayerController, AVR_Test_CodePlayerController::StaticClass, TEXT("AVR_Test_CodePlayerController"), &Z_Registration_Info_UClass_AVR_Test_CodePlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AVR_Test_CodePlayerController), 1957580791U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodePlayerController_h_3906468864(TEXT("/Script/VR_Test_Code"),
		Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodePlayerController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodePlayerController_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
