// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Catgirl_hunterTarget : TargetRules
{
	public Catgirl_hunterTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("Catgirl_hunter");
		ExtraModuleNames.Add("World_gen");
		ExtraModuleNames.Add("Enemies");
		ExtraModuleNames.Add("CharacterAbilities");
	}
}
