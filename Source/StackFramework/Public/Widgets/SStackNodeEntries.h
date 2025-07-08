#pragma once
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/SListView.h"
#include "ViewModels/StackItem.h"
#include "Definition/StackCommonTypes.h"
#include "ViewModels/StackGroup.h"



class UStackRoot;
class UStackRootViewModel;
class UStackSelectionViewModel;
class UStackEntry;
class SStackList;

class SStackNodeEntries : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SStackNodeEntries)
		: _AllowedClasses({ UStackItem::StaticClass(), UStackGroup::StaticClass() })
		{
		}
		SLATE_ARGUMENT(TArray<UClass*>, AllowedClasses)
	SLATE_END_ARGS();

	void Construct(const FArguments& InArgs, UStackRootViewModel& InStackRootViewModel, UStackSelectionViewModel& InNodeSelectionViewModel);
	virtual ~SStackNodeEntries() override;

	virtual bool SupportsKeyboardFocus() const override;
	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	// TO-DO ~ return 'GetCollectedIssueData()'
	bool HasIssuesOrAnyChildHasIssues() const { return false; }

	static EVisibility GetIssueIconVisibility(UStackEntry* StackEntry);

private:
	void RefreshEntryList();
	void AddEntriesRecursive(UStackEntry& EntryToAdd, TArray<UStackEntry*>& OutEntryList, const TArray<UClass*>& AcceptableClasses, TArray<UStackEntry*> ParentChain);

	void EntryExpansionChanged();
	void EntryExpansionInNodeChanged();
	void EntryStructureChanged(EStackStructureChangedFlags Flags);

	void OnSelectionChanged(UStackEntry* NewSelection, ESelectInfo::Type SelectInfo);
	void UpdateSelection();

	TSharedRef<ITableRow> OnGenerateRowForEntry(UStackEntry* Entry, const TSharedRef<STableViewBase>& OwnerTable);

private:
	UStackRootViewModel* StackRootViewModel;
	UStackSelectionViewModel* SelectionViewModel;

	TArray<UStackEntry*> EntryList;
	TMap<FObjectKey, TArray<UStackEntry*>> EntryToParentChain;
	TSharedPtr<SListView<UStackEntry*>> EntryListView;

	TArray<TWeakObjectPtr<UStackEntry>> PreviousSelection;

	TArray<UClass*> AllowedClasses;

	bool bRefreshEntryListPending = false;
	bool bUpdatingSelectionFromStack = false;
	bool bUpdatingStackFromSelection = false;
};
