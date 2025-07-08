#pragma once
#include "StackEntry.h"
#include "StackStatelessModuleGroup.generated.h"



UCLASS()
class UStackStatelessModuleGroup : public UStackEntry
{
	GENERATED_BODY()
public:
	virtual void Initialize(FStackEntryContext InContext);
};