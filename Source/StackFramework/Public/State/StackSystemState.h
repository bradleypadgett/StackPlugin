#pragma once
#include "StackSystemState.generated.h"



class UStackViewState;

UCLASS()
class STACKFRAMEWORK_API UStackSystemState : public UObject
{
	GENERATED_BODY()

public:
	UStackViewState& GetStackViewState() const { return *StackViewState; }

private:
	UPROPERTY()
	TObjectPtr<UStackViewState> StackViewState;
};
