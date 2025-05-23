#pragma once
#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "PanelDesignerGraphNode_Base.generated.h"



/**
 * Base class for all UI Builder Graph Nodes
 */
UCLASS(Abstract)
class PANELDESIGNER_API UPanelDesignerGraphNode_Base : public UEdGraphNode
{
    GENERATED_BODY()

public:

    virtual FLinearColor GetNodeTitleColor() const override;
    // Later: Common functionality for all nodes can go here (e.g., validation, categories, etc.)
};
