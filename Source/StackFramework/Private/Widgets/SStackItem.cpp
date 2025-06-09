#include "Widgets/SStackItem.h"
#include "ViewModels/StackEntry.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"



void SStackItem::Construct(const FArguments& InArgs)
{
	StackEntry = InArgs._Entry;
	SelectionViewModel = InArgs._SelectionViewModel;

	ChildSlot
		[
			BuildContent()
		];
}

TSharedRef<SWidget> SStackItem::BuildContent()
{
	const FText Label = StackEntry
		? StackEntry->GetDisplayName()
		: FText::FromString(TEXT("<Unnamed>"));

	return SNew(SBox)
		.Padding(FMargin(6, 2))
		[
			SNew(STextBlock)
				.Text(Label)
		];
}