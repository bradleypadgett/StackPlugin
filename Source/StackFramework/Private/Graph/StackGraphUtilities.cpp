#include "Graph/StackGraphUtilities.h"
#include "ViewModels/StackRoot.h"
#include "ViewModels/StackEntry.h"
#include "StackNode.h"



UStackNode* FStackGraphUtilities::AddStackNodeToGraph(UEdGraph* Graph, const FVector2D& Location)
{
	UStackNode* NewNode = NewObject<UStackNode>(Graph);
	Graph->AddNode(NewNode);

	NewNode->CreateNewGuid();
	NewNode->PostPlacedNewNode();
	NewNode->AllocateDefaultPins();

	NewNode->NodePosX = Location.X;
	NewNode->NodePosY = Location.Y;

	NewNode->SnapToGrid(16);

	//NewNode->Initialize(/*Get System*/);

	return NewNode;
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
			//if (UStackEntry* Entry = StackNode->GetStackRoot())
			//{
			//	Entries.Add(Entry);
			//}
		}
	}
	return Entries;
}
