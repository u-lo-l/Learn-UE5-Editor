// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LearnEditor : ModuleRules
{
	public LearnEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrivateIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "LearnExtender" });
	}
}
