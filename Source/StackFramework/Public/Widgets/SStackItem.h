#pragma once
#include "Widgets/SCompoundWidget.h"



class UStackEntry;
class UStackSelectionManager;

/*
 * Core visual item for a stack entry.
 * Used inside SStackRow to render interactive content.
 */
class SStackItem : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SStackItem) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UStackEntry* InStackEntry, UStackSelectionManager* InSelectionManager);

private:
	UStackEntry* StackEntry;
	UStackSelectionManager* SelectionManager;

	TSharedRef<SWidget> BuildContent();
};
