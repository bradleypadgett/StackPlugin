#pragma once
#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"



class FUIBuilderGraphController;
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

    static void InitializeBlueprintEditorTabs(FBlueprintEditor* InBlueprint);

    static void InjectModeSwitcherToolbar(FBlueprintEditor* InBlueprint, UUIBuilderBlueprintExtension* InExtension);

private:

    static void RegisterGraphTab(FBlueprintEditor* InBlueprint);

    UUIBuilderGraph* GetOrCreateGraph(FBlueprintEditor* InBlueprint);
  
    TSharedRef<class SDockTab> CreateGraphTab(FBlueprintEditor* InBlueprint, FSpawnTabArgs* InSpawnTabArgs);


};
