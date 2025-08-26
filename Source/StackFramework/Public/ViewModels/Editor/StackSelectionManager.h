#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StackSelectionManager.generated.h"



class UStackEntry;
class UStackSelection;
class UStackRootManager;
class FStackSystemManager;

DECLARE_MULTICAST_DELEGATE(FOnEntrySelectionChanged);

UCLASS()
class STACKFRAMEWORK_API UStackSelectionManager : public UObject
{
public:
	DECLARE_MULTICAST_DELEGATE(FOnSelectionChanged);

private:
	struct FSelectedEntry
	{
		explicit FSelectedEntry(UStackEntry* SelectedEntry);

		const TWeakObjectPtr<UStackEntry> Entry;
		const FGuid HandleID;
		const FString EntryEditorDataKey;
	};

	GENERATED_BODY()

public:
	void Initialize(TSharedRef<FStackSystemManager> InStackSystemManager);

	bool ContainsEntry(UStackEntry* Entry) const;

	void GetSelectedEntries(TArray<UStackEntry*>& OutSelectedEntries) const;
	void UpdateSelectedEntries(const TArray<UStackEntry*>& InSelected, const TArray<UStackEntry*>& InDeselected, bool bClearSelection);


	FOnEntrySelectionChanged& OnEntrySelectionChanged();

private:

	void DeselectEntryInternal(UStackEntry* InDeselectedEntry);

	void UpdateExternalSelectionState();

private:

	TWeakPtr<FStackSystemManager> SystemManagerWeak;

	UPROPERTY()
	TObjectPtr<UStackSelection> SelectionEntry;

	UPROPERTY()
	TObjectPtr<UStackRootManager> SelectedRootManager;

	bool bRefreshIsPending = false;
	bool bIsSystemNodeSelected = false;

	TArray<FSelectedEntry> SelectedEntries;

	FOnEntrySelectionChanged EntrySelectionChangedDelegate;
};
