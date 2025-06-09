#include "Widgets/SStackRow.h"
#include "ViewModels/StackEntry.h"
#include "ViewModels/Editor/StackSelectionViewModel.h"
#include "Widgets/SStackItem.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"



void SStackRow::Construct(const FArguments& InArgs)
{
	StackEntry = InArgs._Entry;
	SelectionViewModel = InArgs._SelectionViewModel;

	ChildSlot
		[
			CreateDisplayWidget()
		];
}

TSharedRef<SWidget> SStackRow::CreateDisplayWidget()
{
	return SNew(SStackItem)
		.Entry(StackEntry)
		.SelectionViewModel(SelectionViewModel);
}
