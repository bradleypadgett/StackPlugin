#include "UIDesignerDefinition.h"
#include "UIDesignerBlueprintEditor.h"



EAssetCommandResult UIDesignerDefinition::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
    UE_LOG(LogTemp, Warning, TEXT("📦 Calling OpenAssets from AssetDefinition"));

    for (UBlueprint* BP : OpenArgs.LoadObjects<UBlueprint>())
    {
        if (BP->GeneratedClass && BP->GeneratedClass->IsChildOf(AActor::StaticClass()))
        {
            UE_LOG(LogTemp, Warning, TEXT("📦 Calling CreateEditor from AssetDefinition"));
            FUIDesignerBlueprintEditor::CreateEditor(OpenArgs.GetToolkitMode(), OpenArgs.ToolkitHost, BP);
            return EAssetCommandResult::Handled;
        }
    }
    return Super::OpenAssets(OpenArgs);
}
