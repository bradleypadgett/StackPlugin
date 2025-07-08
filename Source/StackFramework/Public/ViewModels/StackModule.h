#pragma once
#include "ViewModels/StackItem.h"
#include "StackModule.generated.h"



UCLASS()
class STACKFRAMEWORK_API UStackModule : public UStackItem
{
	GENERATED_BODY()

public:
	UObject* GetAssignmentNode() const { return AssignmentNode; }

private:
	UPROPERTY()
	UObject* AssignmentNode = nullptr; // Placeholder for now
};
