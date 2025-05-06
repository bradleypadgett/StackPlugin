#pragma once
#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"



class FUIBuilderGraphController;
class UUIBuilderBlueprintExtension;
class UUIBuilderGraph;

/*
 * Extends the Blueprint Editor to add a custom "UI Builder Graph" tab.
 */
class FUIBuilderTabRegistrar : public TSharedFromThis<FUIBuilderTabRegistrar>
{
public:

    FUIBuilderTabRegistrar() = default;

    FUIBuilderTabRegistrar(class FBlueprintEditor* InBlueprintEditor);
    ~FUIBuilderTabRegistrar();

    // Subsystem immediately asks to attach the extension to the Blueprint Editor
    void InitializeBlueprintEditorTabs();

    void AddToolbarButtons(FToolBarBuilder& ToolbarBuilder);

private:

    void RegisterGraphTab();

    UUIBuilderBlueprintExtension* GetOrCreateBlueprintExtension(UBlueprint* Blueprint) const;

    UUIBuilderGraph* GetOrCreateGraph(UBlueprint* Blueprint) const;
  
    TSharedRef<class SDockTab> CreateGraphTab(const class FSpawnTabArgs& Args);

    class FBlueprintEditor* BlueprintEditor = nullptr;

    TSharedPtr<FUIBuilderGraphController> OwnedEditor;

    UPROPERTY(Instanced)
    UUIBuilderGraph* UIBuilderGraph;

};
