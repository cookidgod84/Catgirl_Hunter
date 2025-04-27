// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Catgirl_hunter : ModuleRules
{
	public Catgirl_hunter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "Paper2D", "AIModule", "Niagara", "EnhancedInput", "Enemies", "CharacterAbilities" });
    }
}
