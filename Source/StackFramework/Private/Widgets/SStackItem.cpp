#include "Widgets/SStackItem.h"
#include "ViewModels/StackEntry.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/StackStyle.h"



void SStackItem::Construct(const FArguments& InArgs, UStackEntry* InStackEntry, UStackSelectionManager* InSelectionManager)
{
	StackEntry = InStackEntry;
	SelectionManager = InSelectionManager;

	ChildSlot
		[
			BuildContent()
		];
}

TSharedRef<SWidget> SStackItem::BuildContent()
{
	const FText Label = StackEntry ? StackEntry->GetDisplayName() : FText::FromString(TEXT("<Unnamed>"));

	return SNew(SBox)
		.Padding(FMargin(6, 2))
		[
			SNew(STextBlock)
				.Text(Label)
				.TextStyle(FStackStyle::Get(), "StackEditor.GroupHeaderText")
		];
}