#include "Graph/PanelDesignerGraph.h"
#include "Graph/PanelDesignerGraphSchema.h"



UPanelDesignerGraph::UPanelDesignerGraph()
{
    Schema = UPanelDesignerGraphSchema::StaticClass();

    bAllowDeletion = false;
    bAllowRenaming = false;
    bEditable = true;

}

// Double-check after loading
void UPanelDesignerGraph::PostLoad()
{
    Super::PostLoad();

    if (Schema == nullptr)
    {
        Schema = UPanelDesignerGraphSchema::StaticClass();
    }

    // Ensure settings persist after loading
    bAllowDeletion = false;
    bAllowRenaming = false;
    bEditable = true;
}

