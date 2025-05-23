#include "Graph/PanelDesignerGraphEditor.h"
#include "Graph/PanelDesignerGraph.h"
#include "GraphEditorModule.h"
#include "GraphEditorActions.h"
#include "GraphEditor.h"



void SPanelDesignerGraphEditor::Construct(const FArguments& InArgs)
{
    GraphBeingEdited = InArgs._GraphToEdit;

    UE_LOG(LogTemp, Warning, TEXT("✅ SPanelDesignerGraphEditor::Construct fired."));

    FGraphAppearanceInfo AppearanceInfo;
    AppearanceInfo.CornerText = FText::FromString("UI Builder");

    FGraphEditorCommands::Register();

    GraphEditor = SNew(SGraphEditor)
        .GraphToEdit(GraphBeingEdited)
        .Appearance(AppearanceInfo)
        .ShowGraphStateOverlay(false); // Cleaner for now

    ChildSlot
        [
            GraphEditor.ToSharedRef()
        ];
}
