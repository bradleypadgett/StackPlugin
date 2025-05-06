#pragma once
#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "UIBuilderGraphNode_Base.generated.h"



/**
 * Base class for all UI Builder Graph Nodes
 */
UCLASS(Abstract)
class UIBUILDER_API UUIBuilderGraphNode_Base : public UEdGraphNode
{
    GENERATED_BODY()

public:

    virtual FLinearColor GetNodeTitleColor() const override;
    // Later: Common functionality for all nodes can go here (e.g., validation, categories, etc.)
};
