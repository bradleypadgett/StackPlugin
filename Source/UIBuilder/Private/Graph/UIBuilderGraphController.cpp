#include "Graph/UIBuilderGraphController.h"
#include "UIBuilderBlueprintExtension.h"
#include "EdGraph/EdGraph.h"
#include "GraphEditor.h"



FUIBuilderGraphController::FUIBuilderGraphController() {}

void FUIBuilderGraphController::Init(FBlueprintEditor* InEditor, UUIBuilderBlueprintExtension* InExtension, UUIBuilderGraph* InGraph)
{
    BlueprintEditor = InEditor;
    Graph = InGraph;
    Extension = InExtension;

    if (Extension)
    {
        Extension->OnModeChanged().AddLambda([this](FName NewMode)
        {
            // Later: trigger layout switch
            UE_LOG(LogTemp, Log, TEXT("🌀 Mode changed to: %s"), *NewMode.ToString());
        });
    }
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
