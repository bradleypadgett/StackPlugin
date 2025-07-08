#pragma once
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"
#include "ViewModels/StackEntry.h"
#include "ViewModels/Editor/StackRootViewModel.h"


class UStackRoot;
class UStackSelectionViewModel;
class UStackEntry;
class UStackRootViewModel;

/*
* Renders stack sections and entry tree for one stack node.
*/
class SStackList : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SStackList) {}
		SLATE_ARGUMENT(UStackRoot*, Root)
		SLATE_ARGUMENT(UStackSelectionViewModel*, SelectionViewModel)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UStackRootViewModel* InRootViewModel, UStackRoot* InRoot, UStackSelectionViewModel* InSelection);

private:
	TSharedRef<ITableRow> OnGenerateRow(UStackEntry* Entry, const TSharedRef<STableViewBase>& OwnerTable);

	// TO-DO ~ Switch to entry array
	void OnSelectionChanged(UStackEntry* Entry, ESelectInfo::Type SelectInfo);

	void RefreshEntries();

private:
	UStackRoot* Root;
	UStackRootViewModel* RootViewModel;
	UStackSelectionViewModel* SelectionViewModel;

	TSharedPtr<SListView<TSharedRef<UStackRootViewModel::FStackRootContainer>>> HeaderList;
	TSharedPtr<STreeView<UStackEntry*>> Tree;

	TArray<TSharedRef<UStackRootViewModel::FStackRootContainer>> RootContainers;
	TArray<UStackEntry*> RootEntries;
};
