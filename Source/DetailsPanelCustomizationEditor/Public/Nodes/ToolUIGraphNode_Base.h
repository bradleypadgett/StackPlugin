#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "ToolUIGraphNode_Base.generated.h"

/**
 * Base class for all UI Builder Graph Nodes
 */
UCLASS(Abstract)
class DETAILSPANELCUSTOMIZATIONEDITOR_API UToolUIGraphNode_Base : public UEdGraphNode
{
    GENERATED_BODY()

public:

    // Later: Common functionality for all nodes can go here (e.g., validation, categories, etc.)

};
