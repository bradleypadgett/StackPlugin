using UnrealBuildTool;
public class PanelDesignerRuntime : ModuleRules
{
    public PanelDesignerRuntime(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine"
            //"PanelDesigner"
        });
    }
}
