using UnrealBuildTool;

public class LearnAssetDefinition : ModuleRules
{
    public LearnAssetDefinition(ReadOnlyTargetRules Target) : base(Target)
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
            }
        );
    }
}