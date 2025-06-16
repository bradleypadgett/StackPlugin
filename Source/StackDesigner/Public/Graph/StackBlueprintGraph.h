#pragma once
#include "CoreMinimal.h"
#include "Graph/StackGraph.h"
#include "StackBlueprintGraph.generated.h"



/*
 * The actual graph data structure; added to `FunctionGraphs` for saving.
 */
UCLASS()
class STACKDESIGNER_API UStackBlueprintGraph : public UStackGraph
{
    GENERATED_BODY()

public:

    // Constructor
    UStackBlueprintGraph();

    // Override PostLoad
    virtual void PostLoad() override;
};
