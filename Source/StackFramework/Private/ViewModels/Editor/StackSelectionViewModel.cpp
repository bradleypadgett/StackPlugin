#include "ViewModels/Editor/StackSelectionViewModel.h"
#include "ViewModels/Editor/StackSystemViewModel.h"
#include "ViewModels/Editor/StackRootViewModel.h"
#include "ViewModels/Editor/StackHandleViewModel.h"
#include "ViewModels/Editor/StackViewModel.h"
#include "State/StackSystemState.h"
#include "Definition/StackSource.h"
#include "ViewModels/StackSelection.h"
#include "ViewModels/StackEntry.h"



// helps gen.cpp files make UCLASS(), UFUNCTION(), UPROPERTY() stuff work correctly
#include UE_INLINE_GENERATED_CPP_BY_NAME(StackSelectionViewModel)

FGuid GetHandleIDFromEntry(UStackEntry* Entry)
{
	if (Entry->GetStackViewModel().IsValid())
	{
		TSharedPtr<FStackHandleViewModel> HandleViewModel = Entry->GetSystemViewModel()->GetHandleViewModelFromStack(Entry->GetStackViewModel()->GetStackSource()->GetStack());
		if (HandleViewModel.IsValid())
		{
			return HandleViewModel->GetHandleID();
		}
	}
	return FGuid();
}

UStackSelectionViewModel::FSelectedEntry::FSelectedEntry(UStackEntry* SelectedEntry)
	: Entry(SelectedEntry)
	, HandleID(GetHandleIDFromEntry(SelectedEntry))
	, StackViewStateKey(SelectedEntry->GetStackViewStateKey())
{

}

void UStackSelectionViewModel::Initialize(TSharedRef<FStackSystemViewModel> InStackSystemViewModel)
{
	SystemViewModelWeak = InStackSystemViewModel;

	// Creates new Stack Selection
	SelectionEntry = NewObject<UStackSelection>(this);
	SelectionEntry->Initialize(UStackEntry::FStackEntryContext(
		InStackSystemViewModel
		, TSharedPtr<FStackViewModel>()
		, UStackEntry::FCategoryNames::Default
		, UStackEntry::FSubcategoryNames::Default
		, InStackSystemViewModel->GetSystemState().GetStackViewState()
	));

	// Wraps Selection with a dedicated ViewModel
	// Used to show what's selected in Node UI
	SelectedRootViewModel = NewObject<UStackRootViewModel>(this);
	SelectedRootViewModel->Initialize(SelectionEntry);

	bRefreshIsPending = false;
}


bool UStackSelectionViewModel::ContainsEntry(UStackEntry* Entry) const
{
	for (const FSelectedEntry& SelectedEntry : SelectedEntries)
	{
		if (SelectedEntry.Entry == Entry) return true;
	}
	return false;
}

void UStackSelectionViewModel::GetSelectedEntries(TArray<UStackEntry*>& OutSelectedEntries) const
{
	for (const FSelectedEntry& SelectedEntry : SelectedEntries)
	{
		OutSelectedEntries.Add(SelectedEntry.Entry.Get());
	}
}

void UStackSelectionViewModel::UpdateSelectedEntries(const TArray<UStackEntry*>& InSelectedEntries, const TArray<UStackEntry*>& InDeselectedEntries,bool bClearSelection)
{
	bool bSelectionChanged = false;

	if (bClearSelection)
	{
		SelectedEntries.Empty();
		bSelectionChanged = true;
	}
	else
	{
		for (UStackEntry* Deselected : InDeselectedEntries)
		{
			if (ContainsEntry(Deselected))
			{
				DeselectEntryInternal(Deselected);
				bSelectionChanged = true;
			}
		}
	}

	for (UStackEntry* Selected : InSelectedEntries)
	{
		if (!ContainsEntry(Selected))
		{
			SelectedEntries.Add(FSelectedEntry(Selected));
			bSelectionChanged = true;
		}
	}

	if (bSelectionChanged)
	{
		UpdateExternalSelectionState();
	}
}

FOnEntrySelectionChanged& UStackSelectionViewModel::OnEntrySelectionChanged()
{
	return EntrySelectionChangedDelegate;
}

void UStackSelectionViewModel::DeselectEntryInternal(UStackEntry* InDeselectedEntry)
{
	SelectedEntries.RemoveAll([InDeselectedEntry](const FSelectedEntry& SelectionEntry)
	{ 
		if (SelectionEntry.Entry == InDeselectedEntry)
		{
			return true;
		} 
		return false;
	});
}

void UStackSelectionViewModel::UpdateExternalSelectionState()
{
	// TO-DO ~ Refactor
	// Prune child-of-selected entries
	TArray<UStackEntry*> PrunedEntries;
	for (const FSelectedEntry& Entry : SelectedEntries)
	{
		bool bIsChild = false;
		UObject* Outer = Entry.Entry->GetOuter();
		while (Outer != nullptr)
		{
			if (UStackEntry* OuterEntry = Cast<UStackEntry>(Outer))
			{
				if (ContainsEntry(OuterEntry))
				{
					bIsChild = true;
					break;
				}
				Outer = OuterEntry->GetOuter();
			}
			else
			{
				break;
			}
		}

		if (!bIsChild)
		{
			PrunedEntries.Add(Entry.Entry.Get());
		}
	}

	SelectionEntry->SetSelectedEntries(PrunedEntries);
	EntrySelectionChangedDelegate.Broadcast();
}
