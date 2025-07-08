﻿#include "Graph/StackBlueprintGraphEditor.h"
#include "Graph/StackBlueprintGraph.h"
#include "GraphEditorModule.h"
#include "GraphEditorActions.h"
#include "GraphEditor.h"



void SStackBlueprintGraphEditor::Construct(const FArguments& InArgs, UStackBlueprintGraph* InGraphBeingEdited)
{
    GraphBeingEdited = InGraphBeingEdited;

    UE_LOG(LogTemp, Warning, TEXT("✅ SStackBlueprintGraphEditor::Construct fired."));

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
