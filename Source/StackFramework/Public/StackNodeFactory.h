#pragma once
#include "EdGraphUtilities.h"
#include "CoreMinimal.h"



class SGraphNode;
class UEdGraphNode;

/*
 * Maps UStackNode to its visual SStackNode representation.
 */
class STACKFRAMEWORK_API FStackNodeFactory : public FGraphPanelNodeFactory
{
public:
	virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* Node) const override;
};
