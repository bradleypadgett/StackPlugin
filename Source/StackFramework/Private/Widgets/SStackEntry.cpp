#include "Widgets/SStackEntry.h"
#include "Widgets/SStackRow.h"
#include "ViewModels/StackEntry.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"



void SStackEntry::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable)
{
	StackEntry = InArgs._StackEntry;
	SelectionViewModel = InArgs._SelectionViewModel;

	STableRow::Construct(
		STableRow::FArguments()
		.Padding(FMargin(4, 2))
		.Content()
		[
			SNew(SStackRow)
				.Entry(StackEntry)
				.SelectionViewModel(SelectionViewModel)
		],
		InOwnerTable);
}

FText SStackEntry::GetDisplayName() const
{
	return StackEntry ? StackEntry->GetDisplayName() : FText::FromString(TEXT("<Invalid>"));
}
