#pragma once
#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"



class UUIBuilderGraph;

/*
 * A custom sidebar action that will show up in MyBlueprint panel
 */
class FUIBuilderGraphSidebarAction : public FEdGraphSchemaAction
{
public:

    UUIBuilderGraph* Graph;

    FUIBuilderGraphSidebarAction()
        : FEdGraphSchemaAction(
            FText::FromString(TEXT("UI Builder")),      // Category
            FText::FromString(TEXT("UIBuilderGraph")),  // Menu title
            FText::FromString(TEXT("Node graph for customizing Details Panel")), // Tooltip
            0)                                          // Section ID
        , Graph(nullptr) {}
    // Add click functionality later
};
