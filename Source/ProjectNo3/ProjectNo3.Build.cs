// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectNo3 : ModuleRules
{
	public ProjectNo3(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "GameplayTags", "ControlRig", "ActorSequence"});

		PublicIncludePaths.AddRange(new string[] { "ProjectNo3/LDW"});
    }
}
