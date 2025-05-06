#include "Graph/UIBuilderGraphController.h"
#include "EdGraph/EdGraph.h"
#include "GraphEditor.h"



FUIBuilderGraphController::FUIBuilderGraphController() {}

void FUIBuilderGraphController::Init(FBlueprintEditor* InEditor, UUIBuilderGraph* InGraph)
{
    BlueprintEditor = InEditor;
    Graph = InGraph;
    BindCommands();
}

TSharedRef<SWidget> FUIBuilderGraphController::BuildGraphWidget()
{
    FGraphAppearanceInfo Appearance;
    Appearance.CornerText = FText::FromString("UI Builder");

    GraphEditorWidget = SNew(SGraphEditor)
        .GraphToEdit(Graph)
        .Appearance(Appearance)
        .ShowGraphStateOverlay(false);

    return GraphEditorWidget.ToSharedRef();
}

void FUIBuilderGraphController::BindCommands()
{
    // Bind keyboard shortcuts later
}
