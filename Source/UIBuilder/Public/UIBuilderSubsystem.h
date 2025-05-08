#pragma once
#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "Widgets/Docking/SDockTab.h"
#include "UIBuilderTabRegistrar.h"
#include "UIBuilderSubsystem.generated.h"



class UUIBuilderGraph;
class FBlueprintEditor;
class FUIBuilderGraphController;

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

    void OnEditorPreWidgets(const TArray<UObject*>& Assets, IAssetEditorInstance* Instance);
};
