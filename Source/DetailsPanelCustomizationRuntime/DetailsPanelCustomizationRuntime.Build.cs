using UnrealBuildTool;

public class DetailsPanelCustomizationRuntime : ModuleRules
{
    public DetailsPanelCustomizationRuntime(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
        });
    }
}
