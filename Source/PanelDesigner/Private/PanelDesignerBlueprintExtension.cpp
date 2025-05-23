#include "PanelDesignerBlueprintExtension.h"
#include "Graph/PanelDesignerGraph.h"
#include "EdGraph/EdGraph.h"



// Automatically called after custom editor is created. Initializes graph and stores owning blueprint.
void UPanelDesignerBlueprintExtension::PostInitProperties()
{
    Super::PostInitProperties();

    OwningBlueprint = GetTypedOuter<UBlueprint>();
    if (OwningBlueprint)
    {
        EnsurePanelDesignerGraph();
    }
}

// Creates and serializes PanelDesignerGraph into owning blueprint if it doesn't have one
UPanelDesignerGraph* UPanelDesignerBlueprintExtension::EnsurePanelDesignerGraph()
{
    if (PanelDesignerGraph) return PanelDesignerGraph;

    UBlueprint* BP = GetTypedOuter<UBlueprint>();

    for (UEdGraph* Graph : BP->FunctionGraphs)
    {
        if (UPanelDesignerGraph* Found = Cast<UPanelDesignerGraph>(Graph))
        {
            PanelDesignerGraph = Found;
            return PanelDesignerGraph;
        }
    }
    PanelDesignerGraph = NewObject<UPanelDesignerGraph>(BP, TEXT("PanelDesignerGraph"));
    BP->FunctionGraphs.Add(PanelDesignerGraph);
    return PanelDesignerGraph;
}