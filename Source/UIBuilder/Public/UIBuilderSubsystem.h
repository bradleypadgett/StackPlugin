#pragma once
#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "Widgets/Docking/SDockTab.h"
#include "UIDesignerTabs.h"
#include "UIBuilderSubsystem.generated.h"



class FUIDesignerBlueprintEditor;

/*
 * Injects the BlueprintExtension and toolbar buttons on blueprint open (pre-widgets).
 */
UCLASS()
class UIBUILDER_API UUIBuilderSubsystem : public UEditorSubsystem
{
    GENERATED_BODY()

public:

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
 
    virtual void Deinitialize() override;

private:

    FEditorModeTools* GetEditorModeManager() const;

    UUIBuilderBlueprintExtension* EnsureExtension(UBlueprint* BP);

    void OnEditorPreWidgets(const TArray<UObject*>& Assets, IAssetEditorInstance* Instance);
 
    void OnEditorBlueprintOpened(UObject* Asset);
    void OnAssetOpened(UObject* Asset, IAssetEditorInstance* EditorInstance);

    void OnAssetEditorClosed(UObject* Asset, EAssetEditorCloseReason CloseReason);

    TSet<UBlueprint*> BlueprintsReopened;

    TMap<UBlueprint*, TWeakPtr<FUIDesignerBlueprintEditor>> CustomEditors;

};
