// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VR_Test_Code/GrabObjectBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGrabObjectBase() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
	UPackage* Z_Construct_UPackage__Script_VR_Test_Code();
	VR_TEST_CODE_API UClass* Z_Construct_UClass_AGrabObjectBase();
	VR_TEST_CODE_API UClass* Z_Construct_UClass_AGrabObjectBase_NoRegister();
	VR_TEST_CODE_API UClass* Z_Construct_UClass_UGrabComponent_NoRegister();
// End Cross Module References
	void AGrabObjectBase::StaticRegisterNativesAGrabObjectBase()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AGrabObjectBase);
	UClass* Z_Construct_UClass_AGrabObjectBase_NoRegister()
	{
		return AGrabObjectBase::StaticClass();
	}
	struct Z_Construct_UClass_AGrabObjectBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_grabComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_grabComponent;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_objectMesh_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_objectMesh;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AGrabObjectBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_VR_Test_Code,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AGrabObjectBase_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGrabObjectBase_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "GrabObjectBase.h" },
		{ "ModuleRelativePath", "GrabObjectBase.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGrabObjectBase_Statics::NewProp_grabComponent_MetaData[] = {
		{ "AllowPrivateAccess", "" },
		{ "Category", "GrabInfo" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "GrabObjectBase.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGrabObjectBase_Statics::NewProp_grabComponent = { "grabComponent", nullptr, (EPropertyFlags)0x00400000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGrabObjectBase, grabComponent), Z_Construct_UClass_UGrabComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AGrabObjectBase_Statics::NewProp_grabComponent_MetaData), Z_Construct_UClass_AGrabObjectBase_Statics::NewProp_grabComponent_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGrabObjectBase_Statics::NewProp_objectMesh_MetaData[] = {
		{ "AllowPrivateAccess", "" },
		{ "Category", "GrabInfo" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "GrabObjectBase.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AGrabObjectBase_Statics::NewProp_objectMesh = { "objectMesh", nullptr, (EPropertyFlags)0x0040000000080009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AGrabObjectBase, objectMesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AGrabObjectBase_Statics::NewProp_objectMesh_MetaData), Z_Construct_UClass_AGrabObjectBase_Statics::NewProp_objectMesh_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AGrabObjectBase_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGrabObjectBase_Statics::NewProp_grabComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGrabObjectBase_Statics::NewProp_objectMesh,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AGrabObjectBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGrabObjectBase>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AGrabObjectBase_Statics::ClassParams = {
		&AGrabObjectBase::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AGrabObjectBase_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AGrabObjectBase_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AGrabObjectBase_Statics::Class_MetaDataParams), Z_Construct_UClass_AGrabObjectBase_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AGrabObjectBase_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AGrabObjectBase()
	{
		if (!Z_Registration_Info_UClass_AGrabObjectBase.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AGrabObjectBase.OuterSingleton, Z_Construct_UClass_AGrabObjectBase_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AGrabObjectBase.OuterSingleton;
	}
	template<> VR_TEST_CODE_API UClass* StaticClass<AGrabObjectBase>()
	{
		return AGrabObjectBase::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AGrabObjectBase);
	AGrabObjectBase::~AGrabObjectBase() {}
	struct Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_GrabObjectBase_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_GrabObjectBase_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AGrabObjectBase, AGrabObjectBase::StaticClass, TEXT("AGrabObjectBase"), &Z_Registration_Info_UClass_AGrabObjectBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AGrabObjectBase), 844007651U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_GrabObjectBase_h_2814659220(TEXT("/Script/VR_Test_Code"),
		Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_GrabObjectBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_VR_Test_Code_Source_VR_Test_Code_GrabObjectBase_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
