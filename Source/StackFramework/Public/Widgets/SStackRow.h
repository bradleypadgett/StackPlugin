#pragma once
#include "ViewModels/StackEntry.h"
#include "Widgets/Views/STableRow.h"
#include "Widgets/Views/STableViewBase.h"



class UStackEntry;
class UStackSelectionManager;

/*
 * Visual content of a single stack entry row.
 */
class SStackRow : public STableRow<UStackEntry*>
{
public:
	SLATE_BEGIN_ARGS(SStackRow) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UStackEntry* InStackEntry, UStackSelectionManager* InSelectionManager, const TSharedRef<STableViewBase>& InOwnerTableView);

private:
	UStackEntry* StackEntry;
	UStackSelectionManager* SelectionManager;

	TSharedRef<SWidget> CreateDisplayWidget();
};
