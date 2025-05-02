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

    // First Subsystem asks this to spawn in an extension
    static TSharedRef<FUIBuilderEditorExtension> CreateEditorExtension(FBlueprintEditor* InBlueprintEditor);

    // Subsystem immediately asks to attach the extension to the Blueprint Editor
    void InitializeBlueprintEditorTabs();


private:

    void RegisterGraphTab();

    UUIBuilderBlueprintExtension* GetOrCreateBlueprintExtension(UBlueprint* Blueprint) const;

    UUIBuilderGraph* GetOrCreateGraph(UBlueprint* Blueprint) const;
  
    TSharedRef<class SDockTab> CreateGraphTab(const class FSpawnTabArgs& Args);

    class FBlueprintEditor* BlueprintEditor = nullptr;

    TSharedPtr<FUIBuilderEditor> OwnedEditor;

    UPROPERTY(Instanced)
    UUIBuilderGraph* UIBuilderGraph;

};
