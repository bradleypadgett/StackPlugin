#pragma once
#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"



class FUIBuilderEditor;

/*
 * Extends the Blueprint Editor to add a custom "UI Builder Graph" tab.
 */
class FUIBuilderBlueprintExtension : public TSharedFromThis<FUIBuilderBlueprintExtension>
{
public:

    FUIBuilderBlueprintExtension() = default;

    FUIBuilderBlueprintExtension(class FBlueprintEditor* InBlueprintEditor);
    ~FUIBuilderBlueprintExtension();

    // Actually attach the extension to the Blueprint Editor
    void ExtendBlueprintEditor();

    static TSharedRef<FUIBuilderBlueprintExtension> Create(FBlueprintEditor* InBlueprintEditor);

private:

    class FBlueprintEditor* BlueprintEditor = nullptr;

    TSharedPtr<FUIBuilderEditor> OwnedEditor;

    TSharedRef<class SDockTab> SpawnUIBuilderGraphTab(const class FSpawnTabArgs& Args);
};
