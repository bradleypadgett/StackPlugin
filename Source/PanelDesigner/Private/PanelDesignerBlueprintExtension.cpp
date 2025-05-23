#include "PanelDesignerBlueprintExtension.h"
#include "PanelDesignerTabs.h"
#include "Graph/PanelDesignerGraph.h"
#include "EdGraph/EdGraph.h"
#include "PanelDesignerBlueprintEditor.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "BlueprintEditor.h"
#include "GraphEditor.h"



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
