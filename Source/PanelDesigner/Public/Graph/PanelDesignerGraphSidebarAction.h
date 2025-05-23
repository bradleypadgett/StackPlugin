#pragma once
#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"



class UPanelDesignerGraph;

/*
 * A custom sidebar action that will show up in MyBlueprint panel
 */
class FPanelDesignerGraphSidebarAction : public FEdGraphSchemaAction
{
public:

    UPanelDesignerGraph* Graph;

    FPanelDesignerGraphSidebarAction()
        : FEdGraphSchemaAction(
            FText::FromString(TEXT("UI Builder")),      // Category
            FText::FromString(TEXT("PanelDesignerGraph")),  // Menu title
            FText::FromString(TEXT("Node graph for customizing Details Panel")), // Tooltip
            0)                                          // Section ID
        , Graph(nullptr) {}
    // Add click functionality later
};
