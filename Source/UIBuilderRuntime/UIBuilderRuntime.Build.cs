using UnrealBuildTool;
public class UIBuilderRuntime : ModuleRules
{
    public UIBuilderRuntime(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine"
            //"UIBuilder"
        });
    }
}
