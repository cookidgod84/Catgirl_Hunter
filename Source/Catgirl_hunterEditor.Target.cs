// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Catgirl_hunterEditorTarget : TargetRules
{
	public Catgirl_hunterEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("Catgirl_hunter");
		ExtraModuleNames.Add("World_gen");
		ExtraModuleNames.Add("Enemies");
		ExtraModuleNames.Add("CharacterAbilities");
	}
}
