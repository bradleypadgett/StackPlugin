#include "Graph/UIBuilderGraphSchema.h"
#include "Nodes/UIBuilderGraphNode_AddButton.h"
#include "BlueprintNodeSpawner.h"


void UUIBuilderGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
    if (!ContextMenuBuilder.CurrentGraph)
    {
        return;
    }

    UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(UUIBuilderGraphNode_AddButton::StaticClass());

    if (NodeSpawner)
    {
        TSharedPtr<FToolUI_NewNodeAction> NewAction = MakeShared<FToolUI_NewNodeAction>(
            FText::FromString(TEXT("UI Builder")),
            FText::FromString(TEXT("Add UI Button")),
            FText::FromString(TEXT("Adds a button to the UI Graph")),
            0
        );

        NewAction->NodeSpawner = NodeSpawner;

        ContextMenuBuilder.AddAction(NewAction);
    }
}

UEdGraphNode* UUIBuilderGraphSchema::FToolUI_NewNodeAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
    if (!NodeSpawner || !ParentGraph)
    {
        return nullptr;
    }

    UUIBuilderGraphNode_AddButton* NewNode = NewObject<UUIBuilderGraphNode_AddButton>(ParentGraph);
    ParentGraph->AddNode(NewNode, true, false);

    NewNode->NodePosX = Location.X;
    NewNode->NodePosY = Location.Y;

    return NewNode;
}
