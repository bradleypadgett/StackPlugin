#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StackSelectionViewModel.generated.h"



class UStackEntry;
class UStackSelection;
class UStackRootViewModel;
class FStackSystemViewModel;

DECLARE_MULTICAST_DELEGATE(FOnEntrySelectionChanged);

UCLASS()
class STACKFRAMEWORK_API UStackSelectionViewModel : public UObject
{
public:
	DECLARE_MULTICAST_DELEGATE(FOnSelectionChanged);

private:
	struct FSelectedEntry
	{
		explicit FSelectedEntry(UStackEntry* SelectedEntry);

		const TWeakObjectPtr<UStackEntry> Entry;
		const FGuid HandleID;
		const FString StackViewStateKey;
	};

	GENERATED_BODY()

public:
	void Initialize(TSharedRef<FStackSystemViewModel> InStackSystemViewModel);

	bool ContainsEntry(UStackEntry* Entry) const;

	void GetSelectedEntries(TArray<UStackEntry*>& OutSelectedEntries) const;
	void UpdateSelectedEntries(const TArray<UStackEntry*>& InSelected, const TArray<UStackEntry*>& InDeselected, bool bClearSelection);


	FOnEntrySelectionChanged& OnEntrySelectionChanged();

private:

	void DeselectEntryInternal(UStackEntry* InDeselectedEntry);

	void UpdateExternalSelectionState();

private:

	TWeakPtr<FStackSystemViewModel> SystemViewModelWeak;

	UPROPERTY()
	TObjectPtr<UStackSelection> SelectionEntry;

	UPROPERTY()
	TObjectPtr<UStackRootViewModel> SelectedRootViewModel;

	bool bRefreshIsPending = false;
	bool bIsSystemNodeSelected = false;

	TArray<FSelectedEntry> SelectedEntries;

	FOnEntrySelectionChanged EntrySelectionChangedDelegate;
};
