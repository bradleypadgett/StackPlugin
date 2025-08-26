#include "Graph/StackBlueprintGraphSchema.h"
#include "BlueprintNodeSpawner.h"
#include "Editor/StackNode.h"



FText UStackBlueprintGraphSchema::GetGraphCategory(const UEdGraph* Graph) const
{
    return NSLOCTEXT("StackBlueprint", "GraphCategory", "Details UI Builder");
}