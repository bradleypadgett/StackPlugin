#include "Graph/StackNodeSchemaAction.h"
#include "Graph/StackGraphUtilities.h"
#include "StackNode.h"



FStackNodeSchemaAction::FStackNodeSchemaAction()
	: FEdGraphSchemaAction(
		FText::FromString("Stack"),
		FText::FromString("Add Stack Node"),
		FText::FromString("Adds a stack node to the graph."),
		0)
{
}

UEdGraphNode* FStackNodeSchemaAction::PerformAction(
	UEdGraph* ParentGraph,
	UEdGraphPin* FromPin,
	const FVector2D Location,
	bool bSelectNewNode)
{
	return FStackGraphUtilities::AddStackNodeToGraph(ParentGraph, Location);
}
