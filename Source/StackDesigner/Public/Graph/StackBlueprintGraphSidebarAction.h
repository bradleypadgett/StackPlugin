#pragma once
#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"



/*
 * A custom sidebar action that will show up in MyBlueprint panel
 */
class FStackBlueprintGraphSidebarAction : public FEdGraphSchemaAction
{
public:

    UEdGraph* Graph;

    FStackBlueprintGraphSidebarAction()
        : FEdGraphSchemaAction(
            FText::FromString(TEXT("UI Builder")),      // Category
            FText::FromString(TEXT("StackBlueprintGraph")),  // Menu title
            FText::FromString(TEXT("Node graph for customizing Details Panel")), // Tooltip
            0)                                          // Section ID
        , Graph(nullptr) {}
    // Add click functionality later
};
