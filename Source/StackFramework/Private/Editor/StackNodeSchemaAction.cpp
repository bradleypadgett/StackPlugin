#include "Editor/StackNodeSchemaAction.h"
#include "Utilities/StackGraphUtilities.h"
#include "ViewModels/Editor/StackSystemManager.h"
#include "ViewModels/Editor/StackHandleManager.h"
#include "Editor/StackNode.h"



FStackNodeSchemaAction::FStackNodeSchemaAction(TWeakPtr<FStackSystemManager> InStackSystemManager)
	: FEdGraphSchemaAction(
		FText::FromString("Stack"),
		FText::FromString("Add Stack Node"),
		FText::FromString("Adds a stack node to the graph."),
		0), StackSystemManager(InStackSystemManager)
{
}

UEdGraphNode* FStackNodeSchemaAction::PerformAction(
	UEdGraph* ParentGraph,
	UEdGraphPin* FromPin,
	const FVector2D Location,
	bool bSelectNewNode)
{
	if (!StackSystemManager.IsValid())
	{
		return nullptr;
	}

	TSharedPtr<FStackHandleManager> NewHandle = StackSystemManager.Pin()->AddEmptyStackToSystem();
	
	if (!NewHandle.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("FStackNodeSchemaAction: Failed to create new handle in PerformAction. StackSystemManager was valid, but AddEmptyStackToSystem() returned nullptr."));
		return nullptr;

	}
	FGuid NewHandleID = NewHandle->GetHandleID();

	// find the newly created node to satisfy function !
	for (UEdGraphNode* Node : ParentGraph->Nodes)
	{
		if (UStackNode* StackNode = Cast<UStackNode>(Node))
		{
			if (StackNode->GetHandleID() == NewHandleID)
			{
				return StackNode;
			}
		}
	}

	return nullptr;
}
