#include "Graph/UIBuilderGraph.h"
#include "Graph/UIBuilderGraphSchema.h"

// Assign Schema
UUIBuilderGraph::UUIBuilderGraph()
{
    Schema = UUIBuilderGraphSchema::StaticClass();
}

// Douuuble checkin'
void UUIBuilderGraph::PostLoad()
{
    Super::PostLoad();

    if (Schema == nullptr)
    {
        Schema = UUIBuilderGraphSchema::StaticClass();
    }
}

