#pragma once
#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "UIBuilderGraph.generated.h"



/*
 * The actual graph data structure; added to `FunctionGraphs` for saving.
 */
UCLASS()
class UIBUILDER_API UUIBuilderGraph : public UEdGraph
{
    GENERATED_BODY()

public:

    // Constructor
    UUIBuilderGraph();

    // Override PostLoad
    virtual void PostLoad() override;
};
