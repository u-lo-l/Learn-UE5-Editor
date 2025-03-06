// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DHWeapon : ModuleRules
{
	public DHWeapon(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrivateIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				
			}
		);
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				
				"AssetTools",
				"UnrealEd",
				"InputCore",
				"EditorStyle",
				"AssetDefinition"
			}
		);
		//bPrecompile = true;
		//bUsePrecompiled = true;
	}
}
