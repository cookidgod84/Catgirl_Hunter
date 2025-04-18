// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Enemies : ModuleRules
{
	public Enemies(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "Paper2D", "EnhancedInput" });
    }
}
