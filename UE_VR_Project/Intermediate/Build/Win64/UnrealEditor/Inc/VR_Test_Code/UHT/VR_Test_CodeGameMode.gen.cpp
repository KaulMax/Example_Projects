// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VR_Test_Code/VR_Test_CodeGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeVR_Test_CodeGameMode() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_VR_Test_Code();
	VR_TEST_CODE_API UClass* Z_Construct_UClass_AVR_Test_CodeGameMode();
	VR_TEST_CODE_API UClass* Z_Construct_UClass_AVR_Test_CodeGameMode_NoRegister();
// End Cross Module References
	void AVR_Test_CodeGameMode::StaticRegisterNativesAVR_Test_CodeGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AVR_Test_CodeGameMode);
	UClass* Z_Construct_UClass_AVR_Test_CodeGameMode_NoRegister()
	{
		return AVR_Test_CodeGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AVR_Test_CodeGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AVR_Test_CodeGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_VR_Test_Code,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AVR_Test_CodeGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AVR_Test_CodeGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "VR_Test_CodeGameMode.h" },
		{ "ModuleRelativePath", "VR_Test_CodeGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AVR_Test_CodeGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AVR_Test_CodeGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AVR_Test_CodeGameMode_Statics::ClassParams = {
		&AVR_Test_CodeGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AVR_Test_CodeGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AVR_Test_CodeGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_AVR_Test_CodeGameMode()
	{
		if (!Z_Registration_Info_UClass_AVR_Test_CodeGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AVR_Test_CodeGameMode.OuterSingleton, Z_Construct_UClass_AVR_Test_CodeGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AVR_Test_CodeGameMode.OuterSingleton;
	}
	template<> VR_TEST_CODE_API UClass* StaticClass<AVR_Test_CodeGameMode>()
	{
		return AVR_Test_CodeGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AVR_Test_CodeGameMode);
	AVR_Test_CodeGameMode::~AVR_Test_CodeGameMode() {}
	struct Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AVR_Test_CodeGameMode, AVR_Test_CodeGameMode::StaticClass, TEXT("AVR_Test_CodeGameMode"), &Z_Registration_Info_UClass_AVR_Test_CodeGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AVR_Test_CodeGameMode), 3627426327U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeGameMode_h_1890913590(TEXT("/Script/VR_Test_Code"),
		Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_VR_Test_CodeGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
