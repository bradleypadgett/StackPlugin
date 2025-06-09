#pragma once
#include "Widgets/SCompoundWidget.h"



class UStackEntry;
class UStackSelectionViewModel;

/*
 * Visual content of a single stack entry row.
 */
class SStackRow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SStackRow) {}
		SLATE_ARGUMENT(UStackEntry*, Entry)
		SLATE_ARGUMENT(UStackSelectionViewModel*, SelectionViewModel)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	UStackEntry* StackEntry = nullptr;
	UStackSelectionViewModel* SelectionViewModel = nullptr;

	TSharedRef<SWidget> CreateDisplayWidget();
};
