#include "Widgets/SStackRow.h"
#include "ViewModels/StackEntry.h"
#include "ViewModels/Editor/StackSelectionManager.h"
#include "Widgets/SStackItem.h"



void SStackRow::Construct(const FArguments& InArgs, UStackEntry* InStackEntry, UStackSelectionManager* InSelectionManager, const TSharedRef<STableViewBase>& InOwnerTableView)
{
	StackEntry = InStackEntry;
	SelectionManager = InSelectionManager;

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
	return SNew(SStackItem, StackEntry, SelectionManager);
}
