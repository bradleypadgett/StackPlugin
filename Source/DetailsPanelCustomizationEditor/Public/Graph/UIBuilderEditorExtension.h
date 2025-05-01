#pragma once
#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"



class FUIBuilderEditor;
class UUIBuilderBlueprintExtension;
class UUIBuilderGraph;

/*
 * Extends the Blueprint Editor to add a custom "UI Builder Graph" tab.
 */
class FUIBuilderEditorExtension : public TSharedFromThis<FUIBuilderEditorExtension>
{
public:

    FUIBuilderEditorExtension() = default;

    FUIBuilderEditorExtension(class FBlueprintEditor* InBlueprintEditor);
    ~FUIBuilderEditorExtension();

    // Actually attach the extension to the Blueprint Editor
    void ExtendBlueprintEditor();

    static TSharedRef<FUIBuilderEditorExtension> CreateEditorExtension(FBlueprintEditor* InBlueprintEditor);

private:

    void RegisterGraphTab();

    UUIBuilderBlueprintExtension* GetOrCreateBlueprintExtension(UBlueprint* Blueprint) const;

    UUIBuilderGraph* GetOrCreateGraph(UBlueprint* Blueprint) const;


    class FBlueprintEditor* BlueprintEditor = nullptr;

    TSharedPtr<FUIBuilderEditor> OwnedEditor;

    TSharedRef<class SDockTab> CreateUIBuilderGraphTab(const class FSpawnTabArgs& Args);
};
