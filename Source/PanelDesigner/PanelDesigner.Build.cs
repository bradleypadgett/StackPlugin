using UnrealBuildTool;
public class PanelDesigner : ModuleRules
{
    public PanelDesigner(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "Slate",
            "SlateCore",
            "PropertyEditor",
            "UnrealEd",
            "KismetCompiler",
            "BlueprintGraph",
            "GraphEditor",
            "Kismet",
            "EditorSubsystem",
            "PanelDesignerRuntime",
            "NiagaraEditor"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "WorkspaceMenuStructure",
            "AssetDefinition",
            "EngineAssetDefinitions",
            "ToolMenus",
            "WorkspaceMenuStructure"
        });
    }
}