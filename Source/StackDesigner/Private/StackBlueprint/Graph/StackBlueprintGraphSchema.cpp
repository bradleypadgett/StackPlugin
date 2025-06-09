#include "Graph/StackBlueprintGraphSchema.h"
#include "BlueprintNodeSpawner.h"
#include "StackNode.h"



FText UStackBlueprintGraphSchema::GetGraphCategory(const UEdGraph* Graph) const
{
    return NSLOCTEXT("StackBlueprint", "GraphCategory", "Details UI Builder");
}

void UStackBlueprintGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
    if (!ContextMenuBuilder.CurrentGraph)
    {
        return;
    }
    /*
    UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(UStackNode::StaticClass());

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
    }*/
}
/*
UEdGraphNode* UStackBlueprintGraphSchema::FToolUI_NewNodeAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
    if (!NodeSpawner || !ParentGraph)
    {
        return nullptr;
    }

    UStackNode_AddButton* NewNode = NewObject<UStackNode>(ParentGraph);
    ParentGraph->AddNode(NewNode, true, false);

    NewNode->NodePosX = Location.X;
    NewNode->NodePosY = Location.Y;

    return NewNode;
}*/
