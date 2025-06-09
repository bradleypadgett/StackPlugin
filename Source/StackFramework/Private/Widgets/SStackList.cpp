#include "Widgets/SStackList.h"
#include "ViewModels/Editor/StackViewModel.h"
#include "ViewModels/Editor/StackSelectionViewModel.h"
#include "Widgets/SStackEntry.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Views/SListView.h"



void SStackList::Construct(const FArguments& InArgs)
{
	StackViewModel = InArgs._StackViewModel;
	SelectionViewModel = InArgs._SelectionViewModel;

	RefreshEntries();

	ChildSlot
		[
			SAssignNew(ListView, SListView<UStackEntry*>)
				.ListItemsSource(&EntryList)
				.OnGenerateRow(this, &SStackList::OnGenerateRow)
				.OnSelectionChanged(this, &SStackList::OnSelectionChanged)
				.SelectionMode(ESelectionMode::Single)
		];
}

void SStackList::RefreshEntries()
{
	EntryList.Reset();

	if (StackViewModel)
	{
		EntryList.Append(StackViewModel->GetRootEntries());
	}

	if (ListView.IsValid())
	{
		ListView->RequestListRefresh();
	}
}

TSharedRef<ITableRow> SStackList::OnGenerateRow(UStackEntry* Entry, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(SStackEntry, OwnerTable)
		.StackEntry(Entry)
		.SelectionViewModel(SelectionViewModel);
}

void SStackList::OnSelectionChanged(UStackEntry* Entry, ESelectInfo::Type SelectInfo)
{
	if (SelectionViewModel)
	{
		SelectionViewModel->SetSelectedEntry(Entry);
	}
}
