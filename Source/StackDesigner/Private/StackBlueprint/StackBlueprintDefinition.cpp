#include "StackBlueprintDefinition.h"
#include "StackBlueprintEditor.h"



// Handles opening assets. Routes AActor blueprints to use custom Editor
EAssetCommandResult UStackBlueprintDefinition::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
    for (UBlueprint* Blueprint : OpenArgs.LoadObjects<UBlueprint>())
    {
        if (Blueprint->GeneratedClass && Blueprint->GeneratedClass->IsChildOf(AActor::StaticClass()))
        {
            TSharedRef<FStackBlueprintEditor> Editor = MakeShared<FStackBlueprintEditor>();

            Editor->InitBlueprintEditor(OpenArgs.GetToolkitMode(), OpenArgs.ToolkitHost, { Blueprint }, false);

            return EAssetCommandResult::Handled;
        }
    }
    return Super::OpenAssets(OpenArgs);
}