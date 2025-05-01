#pragma once
#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "Widgets/Docking/SDockTab.h"
#include "Graph/UIBuilderBlueprintExtension.h"
#include "UIBuilderSubsystem.generated.h"



class UUIBuilderGraph;
class FBlueprintEditor;
class FUIBuilderEditor;

/**
 * UIBuilderSubsystem
 *
 * Editor-only subsystem that automatically manages injecting
 * a UIBuilderGraphHolder into Blueprints when opened in editor,
 * and extends the Blueprint Editor with the UI Builder tab.
 *
 * - When a Blueprint is opened:
 *   [AssetEditorOpened -> RegisterEditorExtension() -> InjectGraphHolder() -> (Ensure/Add Variable + Ensure/Create Instance)]
 *   [If needed, retries occur using FTSTicker]
 *
 * - After injection:
 *   ExtendBlueprintEditor() sets up custom UI Builder graph tab.
 */
UCLASS()
class DETAILSPANELCUSTOMIZATIONEDITOR_API UUIBuilderSubsystem : public UEditorSubsystem
{
    GENERATED_BODY()

public:

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    /** Called when any asset editor is opened */
    void RegisterEditorExtension(UObject* Asset);

    /** Injects the GraphHolder and Graph into Blueprint if missing */
    void InjectGraphHolder(UBlueprint* BlueprintAsset);

    /** Tries to inject the UIBuilderGraphHolder instance into the Blueprint's CDO */
    bool InjectGraphHolderInstance(UBlueprint* BlueprintAsset);

    UUIBuilderGraph* GetGraphForBlueprint(UBlueprint* BlueprintAsset) const;

private:

    /** Ensures the GraphHolder variable exists in the Blueprint's class (true = newly added) */
    bool EnsureGraphHolderVariable(UBlueprint* BlueprintAsset);

    /** Retries graph injection with FTSTicker if Blueprint isn't ready */
    void DeferGraphHolderInjection(UBlueprint* BlueprintAsset, int32 AttemptsRemaining);

    UPROPERTY()
    TSet<TWeakObjectPtr<UBlueprint>> RegisteredBlueprints;

    TSet<FBlueprintEditor*> ActiveEditors;

    /** Weak reference to the Blueprint Editor */
    TWeakPtr<FBlueprintEditor> BlueprintEditorWeak;

    TMap<UBlueprint*, bool> BlueprintExtensionQueue;

    TArray<TSharedPtr<FUIBuilderBlueprintExtension>> ActiveExtensions;

    /** Stores active UIBuilderEditors to prevent garbage collection */
    TArray<TSharedPtr<FUIBuilderEditor>> ActiveUIBuilderEditors;

};
