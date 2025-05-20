#pragma once
#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"



class UUIBuilderBlueprintExtension;
class UUIBuilderGraph; 
class FSpawnTabArgs;
class FUIDesignerBlueprintEditor;
class FBlueprintEditor;

/*
 * Extends the Blueprint Editor to add a custom "UI Builder Graph" tab.
 */
class FUIDesignerTabs : public TSharedFromThis<FUIDesignerTabs>
{
public:

    FUIDesignerTabs();
    ~FUIDesignerTabs();

    static void RegisterDesignerModeTabs(FUIDesignerBlueprintEditor* InBlueprint, TSharedPtr<FTabManager> InTabManager);

    // Slightly hacky solution, but it works reliably so whatever lol
    static void InjectModeSwitcherToolbar(FUIDesignerBlueprintEditor* InBlueprint, UUIBuilderBlueprintExtension* InExtension);

private:

    static void RegisterGraphEditor(FUIDesignerBlueprintEditor* InBlueprint);
    static void RegisterPreviewTab(FUIDesignerBlueprintEditor* InBlueprint);
    static void RegisterSelectionTab(FUIDesignerBlueprintEditor* InBlueprint);
    static void RegisterVariableTab(FUIDesignerBlueprintEditor* InBlueprint);

    //UUIBuilderGraph* GetOrCreateGraph(FBlueprintEditor* InBlueprint);
  
    //TSharedRef<class SDockTab> CreateGraphTab(FBlueprintEditor* InBlueprint, FSpawnTabArgs* InSpawnTabArgs);


};
