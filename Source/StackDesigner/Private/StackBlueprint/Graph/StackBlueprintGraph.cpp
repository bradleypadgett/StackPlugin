#include "Graph/StackBlueprintGraph.h"
#include "Graph/StackBlueprintGraphSchema.h"



UStackBlueprintGraph::UStackBlueprintGraph()
{
    Schema = UStackBlueprintGraphSchema::StaticClass();

    bAllowDeletion = false;
    bAllowRenaming = false;
    bEditable = true;

}

// Double-check after loading
void UStackBlueprintGraph::PostLoad()
{
    Super::PostLoad();

    if (Schema == nullptr)
    {
        Schema = UStackBlueprintGraphSchema::StaticClass();
    }

    // Ensure settings persist after loading
    bAllowDeletion = false;
    bAllowRenaming = false;
    bEditable = true;
}

