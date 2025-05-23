#include "PanelDesignerDefinition.h"
#include "PanelDesignerBlueprintEditor.h"



// Handles opening assets. Routes AActor blueprints to use custom Editor
EAssetCommandResult UPanelDesignerDefinition::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
    for (UBlueprint* Blueprint : OpenArgs.LoadObjects<UBlueprint>())
    {
        if (Blueprint->GeneratedClass && Blueprint->GeneratedClass->IsChildOf(AActor::StaticClass()))
        {
            TSharedRef<FPanelDesignerBlueprintEditor> Editor = MakeShared<FPanelDesignerBlueprintEditor>();

            Editor->InitBlueprintEditor(OpenArgs.GetToolkitMode(), OpenArgs.ToolkitHost, { Blueprint }, false);

            return EAssetCommandResult::Handled;
        }
    }
    return Super::OpenAssets(OpenArgs);
}