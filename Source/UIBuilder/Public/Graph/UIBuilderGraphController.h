#pragma once
#include "CoreMinimal.h"
#include "UIBuilderGraph.h"



class FBlueprintEditor;
class SGraphEditor;
class UUIBuilderBlueprintExtension;

/*
 * Manages tab layout, mode switching, and UI logic.
 */
class FUIBuilderGraphController : public TSharedFromThis<FUIBuilderGraphController>
{
public:
    FUIBuilderGraphController();

    void Init(FBlueprintEditor* InEditor, UUIBuilderBlueprintExtension* InExtension, UUIBuilderGraph* InGraph);

    TSharedRef<SWidget> BuildGraphWidget();

    UUIBuilderGraph* GetGraph() const { return Graph; }

private:

    FBlueprintEditor* BlueprintEditor = nullptr;
    UUIBuilderGraph* Graph = nullptr;

    TSharedPtr<SGraphEditor> GraphEditorWidget;

    UUIBuilderBlueprintExtension* Extension = nullptr;

    void BindCommands();
};
