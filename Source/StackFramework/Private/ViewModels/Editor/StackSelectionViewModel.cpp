#include "ViewModels/Editor/StackSelectionViewModel.h"
#include "ViewModels/StackEntry.h"

void UStackSelectionViewModel::Initialize()
{
	SelectedEntry = nullptr;
}

void UStackSelectionViewModel::SetSelectedEntry(UStackEntry* Entry)
{
	if (SelectedEntry != Entry)
	{
		SelectedEntry = Entry;
		EntrySelectionChangedDelegate.Broadcast();
	}
}

UStackEntry* UStackSelectionViewModel::GetSelectedEntry() const
{
	return SelectedEntry;
}

FOnEntrySelectionChanged& UStackSelectionViewModel::OnEntrySelectionChanged()
{
	return EntrySelectionChangedDelegate;
}
