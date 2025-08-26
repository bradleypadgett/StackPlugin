#pragma once
#include "EdGraph/EdGraphSchema.h"
#include "StackGraphSchema.generated.h"



class UStackSystem;

/*
 * Schema for Stack-based editor graphs.
 */
UCLASS()
class STACKFRAMEWORK_API UStackGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()

public:
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;

};
