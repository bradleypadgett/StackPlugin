#include "Graph/UIBuilderEditor.h"
#include "EdGraph/EdGraph.h"
#include "GraphEditor.h"



FUIBuilderEditor::FUIBuilderEditor() {}

void FUIBuilderEditor::Init(FBlueprintEditor* InEditor, UUIBuilderGraph* InGraph)
{
    BlueprintEditor = InEditor;
    Graph = InGraph;
    BindCommands();
}

TSharedRef<SWidget> FUIBuilderEditor::BuildGraphWidget()
{
    FGraphAppearanceInfo Appearance;
    Appearance.CornerText = FText::FromString("UI Builder");

    GraphEditorWidget = SNew(SGraphEditor)
        .GraphToEdit(Graph)
        .Appearance(Appearance)
        .ShowGraphStateOverlay(false);

    return GraphEditorWidget.ToSharedRef();
}

void FUIBuilderEditor::BindCommands()
{
    // Bind keyboard shortcuts later
}
