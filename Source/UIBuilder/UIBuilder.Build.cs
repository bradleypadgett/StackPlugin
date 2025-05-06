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
            "BlueprintEditorLibrary"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
        
        });

        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new string[] 
            {

            });

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
