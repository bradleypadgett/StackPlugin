#include "Editor/StackNodeFactory.h"
#include "Editor/StackNode.h"
#include "Widgets/SStackNodeRoot.h"
#include "SGraphNode.h"



TSharedPtr<SGraphNode> FStackNodeFactory::CreateNode(UEdGraphNode* Node) const
{
	if (UStackNode* StackNode = Cast<UStackNode>(Node))
	{
		return SNew(SStackNodeRoot, StackNode);
	}

	return nullptr;
}
