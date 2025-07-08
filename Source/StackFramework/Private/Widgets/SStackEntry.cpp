#include "Widgets/SStackEntry.h"
#include "Widgets/SStackRow.h"
#include "ViewModels/StackEntry.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"



void SStackEntry::Construct(const FArguments& InArgs, UStackEntry* InStackEntry, UStackSelectionViewModel* InSelectionViewModel)
{
	StackEntry = InStackEntry;
	SelectionViewModel = InSelectionViewModel;
	/*
	ChildSlot
		[
			SNew(SStackRow, StackEntry, SelectionViewModel)
		];*/
}

TSharedRef<SWidget> SStackEntry::BuildRowContent()
{
	return SNew(STextBlock).Text(FText::FromString(TEXT("Unnamed Entry")));
}

