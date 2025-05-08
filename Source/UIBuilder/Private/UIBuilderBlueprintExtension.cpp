#include "UIBuilderBlueprintExtension.h"
#include "Graph/UIBuilderGraph.h"
#include "EdGraph/EdGraph.h"



void UUIBuilderBlueprintExtension::PostInitProperties()
{
    Super::PostInitProperties();

    OwningBlueprint = GetTypedOuter<UBlueprint>();
    if (OwningBlueprint)
    {
        EnsureUIBuilderGraph();
    }
}


// Creates and serializes UIBuilderGraph into owning blueprint if it doesn't have one
void UUIBuilderBlueprintExtension::EnsureUIBuilderGraph()
{
    if (UIBuilderGraph) return;

    for (UEdGraph* Graph : OwningBlueprint->FunctionGraphs)
    {
        if (UUIBuilderGraph* Found = Cast<UUIBuilderGraph>(Graph))
        {
            UIBuilderGraph = Found;
            return;
        }
    }

    UIBuilderGraph = NewObject<UUIBuilderGraph>(OwningBlueprint, TEXT("UIBuilderGraph"));
    OwningBlueprint->FunctionGraphs.Add(UIBuilderGraph);
    OwningBlueprint->Modify();
    
}

void UUIBuilderBlueprintExtension::SetCurrentMode(FName InMode)
{
    if (CurrentMode != InMode)
    {
        CurrentMode = InMode;
        ModeChangedDelegate.Broadcast(CurrentMode);
    }
}
