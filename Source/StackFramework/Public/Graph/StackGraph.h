#pragma once
#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "StackGraph.generated.h"



/*
 * Custom graph container for stack node editing.
 */
UCLASS()
class STACKFRAMEWORK_API UStackGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	UStackGraph();
};
