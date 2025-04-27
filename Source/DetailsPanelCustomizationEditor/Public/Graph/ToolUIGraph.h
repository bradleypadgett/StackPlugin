#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "ToolUIGraph.generated.h"

/**
 * Custom UI Builder Graph - holds nodes like AddButton, AddSlider, etc.
 */
UCLASS()
class DETAILSPANELCUSTOMIZATIONEDITOR_API UToolUIGraph : public UEdGraph
{
    GENERATED_BODY()

public:

    // Constructor
    UToolUIGraph();

    // Override PostLoad
    virtual void PostLoad() override;

    // Later: Custom graph utility functions can go here
};
