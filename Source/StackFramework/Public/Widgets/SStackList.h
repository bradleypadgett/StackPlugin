#pragma once
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"
#include "ViewModels/StackEntry.h"
#include "ViewModels/Editor/StackRootManager.h"


class UStackRoot;
class UStackSelectionManager;
class UStackEntry;
class UStackRootManager;

/*
* Renders stack sections and entry tree for one stack node.
*/
class SStackList : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SStackList) {}
		SLATE_ARGUMENT(UStackRoot*, Root)
		SLATE_ARGUMENT(UStackSelectionManager*, SelectionManager)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UStackRootManager* InRootManager, UStackRoot* InRoot, UStackSelectionManager* InSelection);

private:
	TSharedRef<ITableRow> OnGenerateRow(UStackEntry* Entry, const TSharedRef<STableViewBase>& OwnerTable);

	// TO-DO ~ Switch to entry array
	void OnSelectionChanged(UStackEntry* Entry, ESelectInfo::Type SelectInfo);

	void RefreshEntries();

private:
	UStackRoot* Root;
	UStackRootManager* RootManager;
	UStackSelectionManager* SelectionManager;

	TSharedPtr<SListView<TSharedRef<UStackRootManager::FStackRootContainer>>> HeaderList;
	TSharedPtr<STreeView<UStackEntry*>> Tree;

	TArray<TSharedRef<UStackRootManager::FStackRootContainer>> RootContainers;
	TArray<UStackEntry*> RootEntries;
};
