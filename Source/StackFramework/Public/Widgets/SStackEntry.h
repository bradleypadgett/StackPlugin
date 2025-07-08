#pragma once
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "ViewModels/StackEntry.h"



class UStackEntry;
class UStackSelectionViewModel;

/*
 * Widget that displays one row from a stack entry.
 */
class SStackEntry : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SStackEntry) {}
		SLATE_ARGUMENT(UStackEntry*, StackEntry)
		SLATE_ARGUMENT(UStackSelectionViewModel*, SelectionViewModel)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UStackEntry* InStackEntry, UStackSelectionViewModel* InSelectionViewModel);

	virtual TSharedRef<SWidget> BuildRowContent();

protected:
	UStackEntry* StackEntry;
	UStackSelectionViewModel* SelectionViewModel;

};
