#include "Graph/UIBuilderGraphEditor.h"
#include "Graph/UIBuilderGraph.h"
#include "GraphEditorModule.h"
#include "GraphEditorActions.h"
#include "GraphEditor.h"



void SUIBuilderGraphEditor::Construct(const FArguments& InArgs)
{
    GraphBeingEdited = InArgs._GraphToEdit;

    UE_LOG(LogTemp, Warning, TEXT("✅ SUIBuilderGraphEditor::Construct fired."));

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
