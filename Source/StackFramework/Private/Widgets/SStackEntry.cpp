#include "Widgets/SStackEntry.h"
#include "Widgets/SStackRow.h"
#include "ViewModels/StackEntry.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"



void SStackEntry::Construct(const FArguments& InArgs, UStackEntry* InStackEntry, UStackSelectionManager* InSelectionManager)
{
	StackEntry = InStackEntry;
	SelectionManager = InSelectionManager;
	/*
	ChildSlot
		[
			SNew(SStackRow, StackEntry, SelectionManager)
		];*/
}

TSharedRef<SWidget> SStackEntry::BuildRowContent()
{
	return SNew(STextBlock).Text(FText::FromString(TEXT("Unnamed Entry")));
}

