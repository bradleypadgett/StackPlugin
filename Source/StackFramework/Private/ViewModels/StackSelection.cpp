#include "ViewModels/StackSelection.h"
#include "ViewModels/StackEntry.h"
#include "State/StackViewState.h"



#include UE_INLINE_GENERATED_CPP_BY_NAME(StackSelection)

void UStackSelection::Initialize(FStackEntryContext InEntryContext)
{
	Super::Initialize(InEntryContext, TEXT("Selection"));
}

void UStackSelection::SetSelectedEntries(const TArray<UStackEntry*>& InSelectedEntries)
{
	SelectedEntries.Empty();
	for (UStackEntry* Entry : InSelectedEntries)
	{
		SelectedEntries.Add(Entry);
	}
	RefreshChildren();
}

void UStackSelection::RefreshStackChildren(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren, TArray<FStackIssue>& NewIssues)
{
	for (TWeakObjectPtr<UStackEntry> Entry : SelectedEntries)
	{
		if (Entry.IsValid() && !Entry->IsFinalized())
		{
			Entry->SetIsExpanded(true);
			NewChildren.Add(Entry.Get());
		}
	}
}
