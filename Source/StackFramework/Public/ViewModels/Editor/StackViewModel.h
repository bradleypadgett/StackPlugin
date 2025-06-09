#pragma once
#include "CoreMinimal.h"
#include "ViewModels/StackEntry.h"
#include "StackViewModel.generated.h"



class UStackEntry;
class UStackSelectionViewModel;

/*
 * Base stack root. Inherits from StackEntry so it can appear as a visual entry,
 * and contain nested children (groups/items).
 */
UCLASS()
class STACKFRAMEWORK_API UStackViewModel : public UStackEntry
{
	GENERATED_BODY()

public:
	UStackViewModel();

	void Initialize(UObject* InOwnerContext, bool bInIncludeEditorSections = true);

	// UStackEntry overrides
	virtual bool GetCanExpand() const override { return true; }
	virtual bool GetShouldShowInStack() const override { return true; }

	UStackSelectionViewModel* GetSelectionViewModel() const;

	// Return the top-level entries to display
	const TArray<UStackEntry*>& GetRootEntries() const;

	// Refresh stack children
	virtual void RefreshChildren() override;


protected:
	/** Rebuilds children, possibly reusing existing ones. */
	virtual void RefreshChildrenInternal(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren);

	/** Utility for reusing or creating a group entry by name */
	UStackEntry* GetOrCreateGroup(FName GroupID, const TArray<UStackEntry*>& CurrentChildren);

protected:
	UPROPERTY()
	TObjectPtr<UObject> OwnerContext;

	UPROPERTY()
	TArray<UStackEntry*> RootEntries;

	UPROPERTY()
	UStackSelectionViewModel* SelectionViewModel = nullptr;

	UPROPERTY()
	bool bIncludeEditorSections;
};
