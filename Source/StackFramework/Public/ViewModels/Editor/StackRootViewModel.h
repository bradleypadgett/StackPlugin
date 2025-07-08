#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ViewModels/StackEntry.h"
#include "StackRootViewModel.generated.h"



class UStackRoot;
class UStackEntry;

/** Options that control what this stack shows */
USTRUCT()
struct FStackRootViewModelOptions
{
	GENERATED_BODY()

	UPROPERTY()
	bool bIncludeSystemInfo = false;

	UPROPERTY()
	bool bIncludeEmitterInfo = false;
};

UCLASS()
class STACKFRAMEWORK_API UStackRootViewModel : public UObject
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE(FOnExpansionChanged);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnStructureChanged, EStackStructureChangedFlags);

	struct FStackRootContainer
	{
		TWeakObjectPtr<UStackEntry> StackRoot;
		FText DisplayName;

		FStackRootContainer() {}
		FStackRootContainer(UStackEntry* InSection, const FText& InDisplayName)
			: StackRoot(InSection), DisplayName(InDisplayName) {
		}

		bool IsValid() const { return StackRoot.IsValid(); }
	};
	/** Returns top-level stack roots as viewmodels */
	TArray<FStackRootContainer> GetRootContainers() const;

	struct FSearchResult
	{
		TArray<UStackEntry*> EntryPath;
		UStackEntry::FStackSearchItem MatchingItem;
		UStackEntry* GetEntry() const
		{
			return EntryPath.Num() > 0 ? EntryPath.Last() : nullptr;
		}
	};
	/** Initializes stack viewmodel with the given root entries. */
	virtual void Initialize(UStackEntry* InRootEntry);

	/** Clears and re-populates all root sections. */
	virtual void RefreshStack();

	/** Optional: search UI hook */
	void SetSearchText(const FText& NewText);
	FText GetSearchText() const { return SearchText; }

	UStackEntry* GetRootEntry();
	TArray<UStackEntry*> GetRootEntries();

	FOnExpansionChanged& OnExpansionChanged();
	FOnExpansionChanged& OnExpansionInNodeChanged();
	FOnStructureChanged& OnStructureChanged();

protected:


	UPROPERTY()
	FStackRootViewModelOptions Options;

	UPROPERTY()
	FText SearchText;

private:
	UPROPERTY()
	TArray<UStackEntry*> RootEntries;

	TObjectPtr<UStackEntry> RootEntry;

	FOnExpansionChanged ExpansionChangedDelegate;
	FOnExpansionChanged ExpansionInNodeChangedDelegate;
	FOnStructureChanged StructureChangedDelegate;

};
