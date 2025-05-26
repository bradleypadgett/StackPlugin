#include "PanelDesignerDefinition.h"
#include "PanelDesignerEditor.h"



// Handles opening assets. Routes AActor blueprints to use custom Editor
EAssetCommandResult UPanelDesignerDefinition::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
    for (UBlueprint* Blueprint : OpenArgs.LoadObjects<UBlueprint>())
    {
        if (Blueprint->GeneratedClass && Blueprint->GeneratedClass->IsChildOf(AActor::StaticClass()))
        {
            TSharedRef<FPanelDesignerEditor> Editor = MakeShared<FPanelDesignerEditor>();

            Editor->InitBlueprintEditor(OpenArgs.GetToolkitMode(), OpenArgs.ToolkitHost, { Blueprint }, false);

            return EAssetCommandResult::Handled;
        }
    }
    return Super::OpenAssets(OpenArgs);
}