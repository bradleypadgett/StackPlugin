#include "UIBuilderBlueprintExtension.h"
#include "UIDesignerTabs.h"
#include "Graph/UIBuilderGraph.h"
#include "EdGraph/EdGraph.h"
#include "UIDesignerBlueprintEditor.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "BlueprintEditor.h"
#include "GraphEditor.h"



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
UUIBuilderGraph* UUIBuilderBlueprintExtension::EnsureUIBuilderGraph()
{
    if (UIBuilderGraph) return UIBuilderGraph;

    UBlueprint* BP = GetTypedOuter<UBlueprint>();

    for (UEdGraph* Graph : BP->FunctionGraphs)
    {
        if (UUIBuilderGraph* Found = Cast<UUIBuilderGraph>(Graph))
        {
            UIBuilderGraph = Found;
            return UIBuilderGraph;
        }
    }

    UIBuilderGraph = NewObject<UUIBuilderGraph>(BP, TEXT("UIBuilderGraph"));
    BP->FunctionGraphs.Add(UIBuilderGraph);
    return UIBuilderGraph;
}
