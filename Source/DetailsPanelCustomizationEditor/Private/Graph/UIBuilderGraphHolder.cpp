#include "Graph/UIBuilderGraphHolder.h"
#include "Graph/UIBuilderGraph.h"



void UUIBuilderGraphHolder::PostInitProperties()
{
    Super::PostInitProperties();

    if (!UIBuilderGraph)
    {
        // Auto-create the Graph if it doesn't exist
        UIBuilderGraph = NewObject<UUIBuilderGraph>(this, UUIBuilderGraph::StaticClass(), NAME_None, RF_Transactional);

        UE_LOG(LogTemp, Warning, TEXT("UIBuilderGraphHolder: Created new UIBuilderGraph inside Holder!"));
    }
}