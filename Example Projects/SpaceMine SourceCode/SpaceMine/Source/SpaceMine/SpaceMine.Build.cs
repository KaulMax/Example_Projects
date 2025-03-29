// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SpaceMine : ModuleRules
{
	public SpaceMine(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "AIModule" , "NavigationSystem" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "FMODStudio"});
    }
}
