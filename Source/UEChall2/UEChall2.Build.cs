// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UEChall2 : ModuleRules
{
	public UEChall2(ReadOnlyTargetRules Target) : base(Target)
	{
        PrivateDependencyModuleNames.AddRange(new string[] {"ApexDestruction"});
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
