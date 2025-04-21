using UnrealBuildTool;

public class DetailsPanelCustomizationEditor : ModuleRules
{
    public DetailsPanelCustomizationEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "UnrealEd",
            "Slate",
            "SlateCore",
            "PropertyEditor",
            "EditorStyle",
            "InputCore",
            "DetailsPanelCustomizationRuntime"
        });

        PrivateIncludePaths.AddRange(new string[]
        {
            "DetailsPanelCustomizationEditor/Private"
        });

        PublicIncludePaths.AddRange(new string[]
        {
            "DetailsPanelCustomizationEditor/Public"
        });
    }
}
