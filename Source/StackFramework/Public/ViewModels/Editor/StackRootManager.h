#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ViewModels/StackEntry.h"
#include "StackRootManager.generated.h"



class UStackRoot;
class UStackEntry;
class FStackHandleManager;
class FStackSystemManager;

UCLASS()
class STACKFRAMEWORK_API UStackRootManager : public UObject
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
	// Returns top-level stack roots as viewmodels
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

	virtual void InitializeStack(TSharedPtr<FStackSystemManager> InSystemManager, TSharedPtr<FStackHandleManager> InHandle);
	virtual void InitializeStack(UStackEntry* InRootEntry);

	// Clears and re-populates all root sections
	virtual void RefreshStack();

	void SetSearchText(const FText& NewText);
	FText GetSearchText() const { return SearchText; }

	UStackEntry* GetRootEntry();
	TArray<UStackEntry*> GetRootEntries();

	FOnExpansionChanged& OnExpansionChanged();
	FOnExpansionChanged& OnExpansionInNodeChanged();
	FOnStructureChanged& OnStructureChanged();

	void Reset();

protected:

	UPROPERTY()
	FText SearchText;

private:
	void HandleRemoved();

	UPROPERTY()
	TArray<UStackEntry*> RootEntries;

	UPROPERTY()
	TObjectPtr<UStackEntry> RootEntry;

	TWeakPtr<FStackSystemManager> SystemManager;
	TWeakPtr<FStackHandleManager> StackHandleManager;

	FOnExpansionChanged ExpansionChangedDelegate;
	FOnExpansionChanged ExpansionInNodeChangedDelegate;
	FOnStructureChanged StructureChangedDelegate;

};
