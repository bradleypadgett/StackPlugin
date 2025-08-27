#pragma once
#include "EdGraph/EdGraphSchema.h"
#include "CoreMinimal.h"



class FStackSystemManager;

/*
 * Schema action to add a UStackNode to the graph.
 */
class STACKFRAMEWORK_API FStackNodeSchemaAction : public FEdGraphSchemaAction
{
public:
	FStackNodeSchemaAction(TWeakPtr<FStackSystemManager> InStackSystemManager);

	virtual UEdGraphNode* PerformAction(
		UEdGraph* ParentGraph,
		UEdGraphPin* FromPin,
		const FVector2D Location,
		bool bSelectNewNode = true
	) override;

private:
	TWeakPtr<FStackSystemManager> StackSystemManager;
};
