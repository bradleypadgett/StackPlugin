#pragma once
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"



class UStackViewModel;
class UStackSelectionViewModel;
class UStackEntry;

/*
 * Core ListView for rendering stack entries.
 */
class SStackList : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SStackList) {}
		SLATE_ARGUMENT(UStackViewModel*, StackViewModel)
		SLATE_ARGUMENT(UStackSelectionViewModel*, SelectionViewModel)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	TSharedRef<ITableRow> OnGenerateRow(UStackEntry* Entry, const TSharedRef<STableViewBase>& OwnerTable);
	void OnSelectionChanged(UStackEntry* Entry, ESelectInfo::Type SelectInfo);
	void RefreshEntries();

private:
	UStackViewModel* StackViewModel = nullptr;
	UStackSelectionViewModel* SelectionViewModel = nullptr;

	TArray<UStackEntry*> EntryList;
	TSharedPtr<SListView<UStackEntry*>> ListView;
};
