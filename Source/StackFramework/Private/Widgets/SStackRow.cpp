#include "Widgets/SStackRow.h"
#include "ViewModels/StackEntry.h"
#include "ViewModels/Editor/StackSelectionViewModel.h"
#include "Widgets/SStackItem.h"



void SStackRow::Construct(const FArguments& InArgs, UStackEntry* InStackEntry, UStackSelectionViewModel* InSelectionViewModel, const TSharedRef<STableViewBase>& InOwnerTableView)
{
	StackEntry = InStackEntry;
	SelectionViewModel = InSelectionViewModel;

	STableRow<UStackEntry*>::Construct(
		STableRow<UStackEntry*>::FArguments()
		.Padding(FMargin(2.0f)),
		InOwnerTableView
	);

	ChildSlot
		[
			CreateDisplayWidget()
		];
}

TSharedRef<SWidget> SStackRow::CreateDisplayWidget()
{
	return SNew(SStackItem, StackEntry, SelectionViewModel);
}
