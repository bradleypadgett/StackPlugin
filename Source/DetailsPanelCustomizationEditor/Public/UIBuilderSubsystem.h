#pragma once
#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "Widgets/Docking/SDockTab.h"
#include "Graph/UIBuilderEditorExtension.h"
#include "UIBuilderSubsystem.generated.h"



class UUIBuilderGraph;
class FBlueprintEditor;
class FUIBuilderEditor;

/*
 * Editor-only subsystem that automatically manages injecting
 * a UIBuilderGraph into Blueprints when opened in editor,
 * and extends the Blueprint Editor with the UI Builder tab.
 */
UCLASS()
class DETAILSPANELCUSTOMIZATIONEDITOR_API UUIBuilderSubsystem : public UEditorSubsystem
{
    GENERATED_BODY()

public:

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    /** Called when any asset editor is opened */
    void OnBlueprintEditorOpened(UObject* Asset);

private:

    TSet<FBlueprintEditor*> ActiveEditors;

};
