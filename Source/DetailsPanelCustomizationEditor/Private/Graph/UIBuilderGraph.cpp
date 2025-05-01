#include "Graph/UIBuilderGraph.h"
#include "Graph/UIBuilderGraphSchema.h"



UUIBuilderGraph::UUIBuilderGraph()
{
    Schema = UUIBuilderGraphSchema::StaticClass();

    bAllowDeletion = false;
    bAllowRenaming = false;
    bEditable = true;

}

// Double-check after loading
void UUIBuilderGraph::PostLoad()
{
    Super::PostLoad();

    if (Schema == nullptr)
    {
        Schema = UUIBuilderGraphSchema::StaticClass();
    }

    // Ensure settings persist after loading
    bAllowDeletion = false;
    bAllowRenaming = false;
    bEditable = true;
}

