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

	virtual bool CanResetItem() const { return false; }


private:
	FOnAlternateDisplayNameChanged AlternateDisplayNameChangedDelegate;

	UPROPERTY()
	bool bIsFinalized = false;

	UPROPERTY()
	TOptional<FText> AlternateDisplayName;

	UPROPERTY()
	FText TooltipText;
};

UCLASS()
class STACKFRAMEWORK_API UStackItemContent : public UStackEntry
{
	GENERATED_BODY()

public:
	void Initialize(const FStackEntryContext& InEntryContext, FString InStackViewKey, FString InParentItemViewKey);

	bool GetIsAdvanced() const { return bIsAdvanced; }
	void SetIsAdvanced(bool bInAdvanced) { bIsAdvanced = bInAdvanced; }

	bool GetIsHidden() const { return bIsHidden; }
	void SetIsHidden(bool bInHidden) { bIsHidden = bInHidden; }

	virtual bool HasOverriddenContent() const { return false; }

	bool FilterHiddenChildren(const UStackEntry& Child) const { return false; };

protected:
	FString GetParentItemViewKey() const { return ParentItemViewKey; }

private:
	bool FilterAdvancedChildren(const UStackEntry& Child) const { return false; }

private:
	FString ParentItemViewKey;
	bool bIsAdvanced = false;
	bool bIsHidden = false;
};
