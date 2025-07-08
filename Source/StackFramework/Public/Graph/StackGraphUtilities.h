#pragma once
#include "CoreMinimal.h"



class UEdGraph;
class UStackEntry;
class UStackNode;

/*
 * Utility functions for working with stack graphs.
 */
class STACKFRAMEWORK_API FStackGraphUtilities
{
public:
	static UStackNode* AddStackNodeToGraph(UEdGraph* Graph, const FVector2D& Location);
	static void RemoveStackNodeFromGraph(UStackEntry* StackEntry);
	static TArray<UStackEntry*> GetAllStackEntries(UEdGraph* Graph);
};
