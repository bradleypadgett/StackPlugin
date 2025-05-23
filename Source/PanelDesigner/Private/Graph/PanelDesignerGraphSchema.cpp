#include "Graph/PanelDesignerGraphSchema.h"
#include "Nodes/PanelDesignerGraphNode_AddButton.h"
#include "BlueprintNodeSpawner.h"



FText UPanelDesignerGraphSchema::GetGraphCategory(const UEdGraph* Graph) const
{
    return NSLOCTEXT("PanelDesigner", "GraphCategory", "Details UI Builder");
}

void UPanelDesignerGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
    if (!ContextMenuBuilder.CurrentGraph)
    {
        return;
    }

    UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(UPanelDesignerGraphNode_AddButton::StaticClass());

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

UEdGraphNode* UPanelDesignerGraphSchema::FToolUI_NewNodeAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
    if (!NodeSpawner || !ParentGraph)
    {
        return nullptr;
    }

    UPanelDesignerGraphNode_AddButton* NewNode = NewObject<UPanelDesignerGraphNode_AddButton>(ParentGraph);
    ParentGraph->AddNode(NewNode, true, false);

    NewNode->NodePosX = Location.X;
    NewNode->NodePosY = Location.Y;

    return NewNode;
}
