using UnrealBuildTool;
public class StackFramework : ModuleRules
{
    public StackFramework(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "Slate",
            "SlateCore",
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "PropertyEditor",
            "UnrealEd",
            "GraphEditor",
            "InputCore"
        });
    }
}