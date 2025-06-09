#pragma once
#include "CoreMinimal.h"



class UEdGraph;
class UStackEntry;

namespace FStackGraphUtilities
{
	STACKFRAMEWORK_API void AddStackNodeToGraph(UEdGraph* Graph, const FVector2D& Location);

	STACKFRAMEWORK_API void RemoveStackNodeFromGraph(UStackEntry* StackEntry);

	STACKFRAMEWORK_API TArray<UStackEntry*> GetAllStackEntries(UEdGraph* Graph);
}
