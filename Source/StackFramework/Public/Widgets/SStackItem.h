#pragma once
#include "Widgets/SCompoundWidget.h"



class UStackEntry;
class UStackSelectionViewModel;

/*
 * Core visual item for a stack entry.
 * Used inside SStackRow to render interactive content.
 */
class SStackItem : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SStackItem) {}
		SLATE_ARGUMENT(UStackEntry*, Entry)
		SLATE_ARGUMENT(UStackSelectionViewModel*, SelectionViewModel)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	UStackEntry* StackEntry = nullptr;
	UStackSelectionViewModel* SelectionViewModel = nullptr;

	TSharedRef<SWidget> BuildContent();
};
