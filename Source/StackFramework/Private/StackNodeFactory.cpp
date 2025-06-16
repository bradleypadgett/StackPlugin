#include "StackNodeFactory.h"
#include "StackNode.h"
#include "Widgets/SStackNode.h"
#include "SGraphNode.h"



TSharedPtr<SGraphNode> FStackNodeFactory::CreateNode(UEdGraphNode* Node) const
{
	if (UStackNode* StackNode = Cast<UStackNode>(Node))
	{
		return SNew(SStackNode, StackNode);
	}

	return nullptr;
}
