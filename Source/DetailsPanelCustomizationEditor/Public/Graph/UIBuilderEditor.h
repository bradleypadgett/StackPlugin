#pragma once
#include "CoreMinimal.h"
#include "UIBuilderGraph.h"



class FBlueprintEditor;
class SGraphEditor;

// If I ever want to switch to having a standalone .uasset, switch over to FAssetEditorToolkit

/*
 * Main editor controller / window, manages tab layouts, undo/redo
 */
class FUIBuilderEditor : public TSharedFromThis<FUIBuilderEditor>
{
public:
    FUIBuilderEditor();

    void Init(FBlueprintEditor* InEditor, UUIBuilderGraph* InGraph);

    TSharedRef<SWidget> BuildGraphWidget();

    UUIBuilderGraph* GetGraph() const { return Graph; }

private:

    FBlueprintEditor* BlueprintEditor = nullptr;
    UUIBuilderGraph* Graph = nullptr;

    TSharedPtr<SGraphEditor> GraphEditorWidget;

    void BindCommands();
};
