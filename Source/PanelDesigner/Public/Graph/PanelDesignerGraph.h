#pragma once
#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "PanelDesignerGraph.generated.h"



/*
 * The actual graph data structure; added to `FunctionGraphs` for saving.
 */
UCLASS()
class PANELDESIGNER_API UPanelDesignerGraph : public UEdGraph
{
    GENERATED_BODY()

public:

    // Constructor
    UPanelDesignerGraph();

    // Override PostLoad
    virtual void PostLoad() override;
};
