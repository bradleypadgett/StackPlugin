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
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UStackEntry* InStackEntry, UStackSelectionViewModel* InSelectionViewModel);

private:
	UStackEntry* StackEntry;
	UStackSelectionViewModel* SelectionViewModel;

	TSharedRef<SWidget> BuildContent();
};
