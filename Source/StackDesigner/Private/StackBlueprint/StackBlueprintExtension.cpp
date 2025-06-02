#include "StackBlueprintExtension.h"
#include "Graph/StackBlueprintGraphSchema.h"
#include "Graph/StackBlueprintGraph.h"
#include "EdGraph/EdGraph.h"



// Creates and serializes StackBlueprintGraph into owning blueprint if it doesn't have one
TObjectPtr<UStackBlueprintGraph> UStackBlueprintExtension::EnsureStackBlueprintGraph()
{
    UBlueprint* Blueprint = GetTypedOuter<UBlueprint>();

    if (StackBlueprintGraph) 
    {
        if (StackBlueprintGraph->Schema == UStackBlueprintGraphSchema::StaticClass())
        {
            StackBlueprintGraph->Schema = UStackBlueprintGraphSchema::StaticClass();
            return StackBlueprintGraph;

        }
        UE_LOG(LogTemp, Error, TEXT("Designer graph has incorrect schema! Removing it to avoid crash."));
        Blueprint->FunctionGraphs.Remove(StackBlueprintGraph);
    }

    UE_LOG(LogTemp, Warning, TEXT("Creating Graph inside extension!"));
    StackBlueprintGraph = NewObject<UStackBlueprintGraph>(Blueprint, TEXT("Designer"), RF_Transactional);
    StackBlueprintGraph->Schema = UStackBlueprintGraphSchema::StaticClass();

    return StackBlueprintGraph;
}