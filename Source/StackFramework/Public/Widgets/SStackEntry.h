#pragma once
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "ViewModels/StackEntry.h"



class UStackEntry;
class UStackSelectionViewModel;

/*
 * Widget that displays one row from a stack entry.
 * Will render name, icon, rename support, etc. (later).
 */
class SStackEntry : public STableRow<UStackEntry*>
{
public:
	SLATE_BEGIN_ARGS(SStackEntry) {}
		SLATE_ARGUMENT(UStackEntry*, StackEntry)
		SLATE_ARGUMENT(UStackSelectionViewModel*, SelectionViewModel)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable);

private:
	TSharedRef<SWidget> CreateContent();

	FText GetDisplayName() const;

private:
	UStackEntry* StackEntry = nullptr;
	UStackSelectionViewModel* SelectionViewModel = nullptr;

};
