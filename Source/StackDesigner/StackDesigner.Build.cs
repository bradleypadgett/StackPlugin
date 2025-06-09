using UnrealBuildTool;
public class StackDesigner : ModuleRules
{
    public StackDesigner(ReadOnlyTargetRules Target) : base(Target)
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
            "StackFramework",
            "StackNodes"
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