// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CharacterAbilities : ModuleRules
{
	public CharacterAbilities(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "Paper2D", "AIModule", "Niagara", "EnhancedInput" });
    }
}
