#include "ViewModels/StackItem.h"

void UStackItemContent::Initialize(const FStackEntryContext& InEntryContext, FString InStackViewKey, FString InParentItemViewKey)
{
	Super::Initialize(InEntryContext, InStackViewKey);
	ParentItemViewKey = InParentItemViewKey;
	bIsAdvanced = false;
	bIsHidden = false;
	// TO-DO ~ Initialize filtering
}
