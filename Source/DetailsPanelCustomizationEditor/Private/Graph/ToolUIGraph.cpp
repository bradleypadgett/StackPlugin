#include "Graph/ToolUIGraph.h"
#include "Graph/ToolUIGraphSchema.h"

// Assign Schema
UToolUIGraph::UToolUIGraph()
{
    Schema = UToolUIGraphSchema::StaticClass();
}

// Douuuble checkin'
void UToolUIGraph::PostLoad()
{
    Super::PostLoad();

    if (Schema == nullptr)
    {
        Schema = UToolUIGraphSchema::StaticClass();
    }
}

