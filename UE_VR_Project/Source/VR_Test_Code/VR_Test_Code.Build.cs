// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VR_Test_Code : ModuleRules
{
	public VR_Test_Code(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "XRBase" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" , "XRBase", "HeadMountedDisplay" });
	}
}
