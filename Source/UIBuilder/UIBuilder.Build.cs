using UnrealBuildTool;
public class UIBuilder : ModuleRules
{
    public UIBuilder(ReadOnlyTargetRules Target) : base(Target)
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
            "BlueprintEditorLibrary",
            "EditorSubsystem",
            "UIBuilderRuntime"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "WorkspaceMenuStructure",
            "AssetDefinition",
            "EngineAssetDefinitions"
        });
    }
}
