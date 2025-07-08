#pragma once
#include "StackEntry.h"
#include "StackStatelessGroup.generated.h"



UCLASS()
class UStackStatelessGroup : public UStackEntry
{
	GENERATED_BODY()
public:
	virtual void Initialize(FStackEntryContext InContext);
};