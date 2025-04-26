using UnrealBuildTool;

public class DetailsPanelCustomizationEditor : ModuleRules
{
    public DetailsPanelCustomizationEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] {
            "DetailsPanelCustomizationEditor/Public"
        });

        PrivateIncludePaths.AddRange(new string[] {
            "DetailsPanelCustomizationEditor/Private"
        });

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "Slate",
            "SlateCore",
            "PropertyEditor",
            "UnrealEd"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicDefinitions.Add("DETAILSCUSTOMIZATIONEDITOR_API=__declspec(dllexport)");
    }
}
