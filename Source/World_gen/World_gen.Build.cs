// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class World_gen : ModuleRules
{
	public World_gen(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput" });
		//PublicDependencyModuleNames.AddRange(new string[] { "Catgirl_hunter" });
    }
}
