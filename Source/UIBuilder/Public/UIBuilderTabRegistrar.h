#pragma once
#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"



class FUIBuilderTabManager;
class UUIBuilderBlueprintExtension;
class UUIBuilderGraph; 
class FSpawnTabArgs;
class FBlueprintEditor;

/*
 * Extends the Blueprint Editor to add a custom "UI Builder Graph" tab.
 */
class FUIBuilderTabRegistrar : public TSharedFromThis<FUIBuilderTabRegistrar>
{
public:

    //FUIBuilderTabRegistrar() = default;

    FUIBuilderTabRegistrar();
    ~FUIBuilderTabRegistrar();

    static void InitializeUIBuilderTabs(FBlueprintEditor* InBlueprint);

    static void InjectModeSwitcherToolbar(FBlueprintEditor* InBlueprint, UUIBuilderBlueprintExtension* InExtension);

private:

    static void RegisterGraphEditor(FBlueprintEditor* InBlueprint);
    static void RegisterPreviewTab(FBlueprintEditor* InBlueprint);
    static void RegisterSelectionTab(FBlueprintEditor* InBlueprint);
    static void RegisterVariableTab(FBlueprintEditor* InBlueprint);

    //UUIBuilderGraph* GetOrCreateGraph(FBlueprintEditor* InBlueprint);
  
    //TSharedRef<class SDockTab> CreateGraphTab(FBlueprintEditor* InBlueprint, FSpawnTabArgs* InSpawnTabArgs);


};
