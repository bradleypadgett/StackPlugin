using UnrealBuildTool;

public class DetailsPanelCustomizationEditor : ModuleRules
{
    public DetailsPanelCustomizationEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "Slate",
            "SlateCore",
            "InputCore",
            "PropertyEditor",
            "KismetCompiler",
            "BlueprintGraph",
            "GraphEditor"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "EditorStyle",
            "Projects"
        });

        if (Target.bBuildEditor)
        {
            PublicDependencyModuleNames.AddRange(new string[]
            {
                "UnrealEd",
                "EditorSubsystem",
                "ToolMenus",
                "AssetTools"
            });
        }
    }
}
