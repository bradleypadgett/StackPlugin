#pragma once
#include "CoreMinimal.h"

// TO-DO ~ might remove this tbh

class UEdGraph;
class UStackEntry;
class UStackNode;
class UStackSystem;

/*
 * Utility functions for working with stack graphs.
 */
class STACKFRAMEWORK_API FStackGraphUtilities
{
public:

	//static UStackNode* AddStackNodeToGraph(UStackSystem* InSystem, UEdGraph* Graph, const FVector2D& Location);
	static void RemoveStackNodeFromGraph(UStackEntry* StackEntry);
	static TArray<UStackEntry*> GetAllStackEntries(UEdGraph* Graph);
};
