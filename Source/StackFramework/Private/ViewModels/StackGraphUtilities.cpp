#include "ViewModels/StackGraphUtilities.h"
#include "ViewModels/Editor/StackViewModel.h"
#include "ViewModels/StackEntry.h"
#include "StackNode.h"



void FStackGraphUtilities::AddStackNodeToGraph(UEdGraph* Graph, const FVector2D& Location)
{
	if (!Graph) return;

	// Create a new node
	UStackNode* NewNode = NewObject<UStackNode>(Graph);
	Graph->AddNode(NewNode, /*bFromUI=*/true, /*bSelectNewNode=*/true);

	NewNode->NodePosX = Location.X;
	NewNode->NodePosY = Location.Y;
	NewNode->SnapToGrid(16);
}

void FStackGraphUtilities::RemoveStackNodeFromGraph(UStackEntry* StackEntry)
{
	if (!StackEntry) return;

	UStackNode* StackNode = Cast<UStackNode>(StackEntry->GetOuter());
	if (StackNode && StackNode->GetGraph())
	{
		StackNode->GetGraph()->RemoveNode(StackNode);
	}
}

TArray<UStackEntry*> FStackGraphUtilities::GetAllStackEntries(UEdGraph* Graph)
{
	TArray<UStackEntry*> Entries;
	if (!Graph) return Entries;

	for (UEdGraphNode* Node : Graph->Nodes)
	{
		if (UStackNode* StackNode = Cast<UStackNode>(Node))
		{
			if (UStackEntry* Entry = StackNode->GetStackViewModel())
			{
				Entries.Add(Entry);
			}
		}
	}
	return Entries;
}
