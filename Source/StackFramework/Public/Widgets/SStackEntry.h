#pragma once
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "ViewModels/StackEntry.h"



class UStackEntry;
class UStackSelectionManager;

/*
 * Widget that displays one row from a stack entry.
 */
class SStackEntry : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SStackEntry) {}
		SLATE_ARGUMENT(UStackEntry*, StackEntry)
		SLATE_ARGUMENT(UStackSelectionManager*, SelectionManager)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UStackEntry* InStackEntry, UStackSelectionManager* InSelectionManager);

	virtual TSharedRef<SWidget> BuildRowContent();

protected:
	UStackEntry* StackEntry;
	UStackSelectionManager* SelectionManager;

};
