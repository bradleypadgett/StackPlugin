#include "EditorData/StackSystemEditorData.h"
#include "EdGraph/EdGraph.h"
#include "Editor/StackGraphSchema.h"
#include "Editor/StackNode.h"
#include "StackSystem.h"
#include "Editor/StackGraph.h"



#include UE_INLINE_GENERATED_CPP_BY_NAME(StackSystemEditorData)

void UStackSystemEditorData::PostInitProperties()
{
	Super::PostInitProperties();

	if (!HasAnyFlags(RF_ClassDefaultObject | RF_NeedLoad))
	{
		// e.g., create a default graph
		SystemGraph = NewObject<UStackGraph>(this, TEXT("StackOverview"), RF_Transactional);
		SystemGraph->Schema = UStackGraphSchema::StaticClass();
	}
}

UEdGraph* UStackSystemEditorData::GetSystemGraph()
{
	return SystemGraph;
}

void UStackSystemEditorData::SyncSystemGraph(UStackSystem& InSystem)
{
	TArray<UStackNode*> OverviewNodes;
	SystemGraph->GetNodesOfClass(OverviewNodes);

	UStackNode* LeftNode = nullptr;
	UStackNode* RightNode = nullptr;

	for (UStackNode* Node : OverviewNodes)
	{
		if (LeftNode == nullptr || Node->NodePosX < LeftNode->NodePosX)
		{
			LeftNode = Node;
		}
		if (RightNode == nullptr || Node->NodePosX > RightNode->NodePosX)
		{
			RightNode = Node;
		}
	}


	UStackNode* SystemNode = nullptr;
	TSet<UStackNode*> UsedNodes;

	for (UStackNode* Node : OverviewNodes)
	{
		if (!Node->GetHandleID().IsValid()) // system node
		{
			SystemNode = Node;
			UsedNodes.Add(Node);
		}
		else
		{
			FGuid NodeGuid = Node->GetHandleID();
			for (const FStackHandle& Handle : InSystem.GetHandles())
			{
				if (Handle.GetHandleID() == NodeGuid)
				{
					UsedNodes.Add(Node);
					break;
				}
			}
		}
	}


	if (SystemNode == nullptr)
	{
		SystemGraph->Modify();

		FGraphNodeCreator<UStackNode> Creator(*SystemGraph);
		UStackNode* NewSystemNode = Creator.CreateNode(false);
		NewSystemNode->Initialize(&InSystem, FGuid());

		FVector2D SystemLocation = LeftNode != nullptr
			? FVector2D(LeftNode->NodePosX - 400, LeftNode->NodePosY)
			: SystemGraph->GetGoodPlaceForNewNode();

		NewSystemNode->NodePosX = SystemLocation.X;
		NewSystemNode->NodePosY = SystemLocation.Y;

		Creator.Finalize();

		SystemNode = NewSystemNode;
	}



	// Handle each StackHandle
	for (const FStackHandle& Handle : InSystem.GetHandles())
	{
		UStackNode* MatchingNode = nullptr;

		for (UStackNode* Node : OverviewNodes)
		{
			if (Node->GetHandleID() == Handle.GetHandleID())
			{
				MatchingNode = Node;
				break;
			}
		}

		if (MatchingNode == nullptr)
		{
			SystemGraph->Modify();

			FGraphNodeCreator<UStackNode> Creator(*SystemGraph);
			UStackNode* NewNode = Creator.CreateNode(false);
			NewNode->Initialize(&InSystem, Handle.GetHandleID());

			FVector2D Pos = RightNode != nullptr
				? FVector2D(RightNode->NodePosX + 400, RightNode->NodePosY)
				: SystemGraph->GetGoodPlaceForNewNode();

			NewNode->NodePosX = Pos.X;
			NewNode->NodePosY = Pos.Y;

			Creator.Finalize();

			RightNode = NewNode;
			MatchingNode = NewNode;
		}

		MatchingNode->Modify();
		//MatchingNode->SetEnabledState(Handle.GetIsEnabled() ? ENodeEnabledState::Enabled : ENodeEnabledState::Disabled);
	}

	for (UStackNode* Node : OverviewNodes)
	{
		if (!UsedNodes.Contains(Node))
		{
			Node->Modify();
			Node->DestroyNode();
		}
	}

	// Notify UI
	SystemGraph->NotifyGraphChanged();
}
