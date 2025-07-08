#pragma once
#include "Misc/Optional.h"
#include "StackEntry.h"
#include "StackItem.generated.h"



UCLASS()
class STACKFRAMEWORK_API UStackItem : public UStackEntry
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE(FOnAlternateDisplayNameChanged);
	FOnAlternateDisplayNameChanged& OnAlternateDisplayNameChanged() { return AlternateDisplayNameChangedDelegate; }

	bool IsFinalized() const { return bIsFinalized; }
	TOptional<FText> GetAlternateDisplayName() const { return AlternateDisplayName; }
	FText GetTooltipText() const { return TooltipText; }

private:
	FOnAlternateDisplayNameChanged AlternateDisplayNameChangedDelegate;

	UPROPERTY()
	bool bIsFinalized = false;

	UPROPERTY()
	TOptional<FText> AlternateDisplayName;

	UPROPERTY()
	FText TooltipText;
};
