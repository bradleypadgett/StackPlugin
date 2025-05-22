#include "UIDesignerDefinition.h"
#include "UIDesignerBlueprintEditor.h"



EAssetCommandResult UIDesignerDefinition::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{

    UE_LOG(LogTemp, Warning, TEXT("📦 Calling OpenAssets from AssetDefinition"));

    EToolkitMode::Type Mode = OpenArgs.GetToolkitMode();
    const TCHAR* ModeStr = TEXT("Unknown");
    switch (Mode)
    {
    case EToolkitMode::Standalone:     ModeStr = TEXT("Standalone"); break;
    case EToolkitMode::WorldCentric:   ModeStr = TEXT("WorldCentric"); break;
    }
    UE_LOG(LogTemp, Warning, TEXT("📦 Mode: %s"), ModeStr);

    UE_LOG(LogTemp, Warning, TEXT("📦 ToolkitHost is valid? %s"), OpenArgs.ToolkitHost.IsValid() ? TEXT("Yes") : TEXT("No"));

    for (UBlueprint* Blueprint : OpenArgs.LoadObjects<UBlueprint>())
    {
        if (Blueprint->GeneratedClass && Blueprint->GeneratedClass->IsChildOf(AActor::StaticClass()))
        {
            TSharedRef<FUIDesignerBlueprintEditor> Editor = MakeShared<FUIDesignerBlueprintEditor>();
            Editor->InitBlueprintEditor(EToolkitMode::Standalone, nullptr, { Blueprint }, false);

            return EAssetCommandResult::Handled;
        }
    }
    return Super::OpenAssets(OpenArgs);
}