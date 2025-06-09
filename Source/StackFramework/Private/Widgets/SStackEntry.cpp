#include "Widgets/SStackEntry.h"
#include "Widgets/SStackRow.h"
#include "ViewModels/StackEntry.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"



void SStackEntry::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable)
{
	STableRow::Construct(STableRow::FArguments(), InOwnerTable);

	StackEntry = InArgs._StackEntry;
	SelectionViewModel = InArgs._SelectionViewModel;

	SNew(SStackRow)
		.Entry(StackEntry)
		.SelectionViewModel(SelectionViewModel);
}


TSharedRef<SWidget> SStackEntry::CreateContent()
{
	const FText DisplayName = StackEntry
		? StackEntry->GetDisplayName()
		: FText::FromString(TEXT("<Invalid>"));

	return SNew(SBox)
		.Padding(FMargin(4, 2))
		[
			SNew(STextBlock)
				.Text(DisplayName)
				.Font(FAppStyle::GetFontStyle("NormalFont"))
		];
}


FText SStackEntry::GetDisplayName() const
{
	return StackEntry ? StackEntry->GetDisplayName() : FText::FromString(TEXT("<Invalid>"));
}
