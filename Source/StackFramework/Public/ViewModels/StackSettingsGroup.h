#pragma once
#include "StackEntry.h"
#include "StackSettingsGroup.generated.h"



UCLASS()
class UStackSettingsGroup : public UStackEntry
{
	GENERATED_BODY()
public:
	virtual void Initialize(FStackEntryContext InContext);
};