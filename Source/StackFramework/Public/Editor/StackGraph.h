#pragma once
#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "StackGraph.generated.h"



class FStackSystemManager;

/*
 * Custom graph container for stack node editing.
 */
UCLASS()
class STACKFRAMEWORK_API UStackGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	UStackGraph();

	void Initialize(TSharedPtr<FStackSystemManager> InSystemManager);

	TWeakPtr<FStackSystemManager> SystemManagerWeak;
};
