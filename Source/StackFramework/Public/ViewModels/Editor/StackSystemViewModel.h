#pragma once
#include "CoreMinimal.h"
#include "Templates/SharedPointer.h"



class UStackRoot;
class UStackEntry;
class SWidget;
class UStack;
class UStackSystemData;
class UStackRootViewModel;
class UStackSelectionViewModel;
class FStackRootViewModel;
class FStackHandleViewModel;

/*
 * Editor-level ViewModel to coordinate stack nodes, selection,
 * and inject shared features like Palette, TabManager integration, etc.
 */
class STACKFRAMEWORK_API FStackSystemViewModel : public TSharedFromThis<FStackSystemViewModel>
{
public:
	FStackSystemViewModel();
	virtual ~FStackSystemViewModel() {}

	void Initialize(UStack* InStack);

	virtual UStack* GetStack() const;
	UStackSystemData& GetSystemData() const;

	void AddStack(UStack* InStack);
	TArray<UStack*> GetAllStacks() const;

	UStackSelectionViewModel* GetSelectionViewModel() const;

	TSharedPtr<FStackHandleViewModel> GetHandleViewModelFromID(const FGuid& InHandleID) const;
	TSharedPtr<FStackHandleViewModel> GetHandleViewModelFromStack(const UStack& InStack) const;

	void SetActiveStack(UStack* InStack);
	UStack* GetActiveStack() const;

	void SetSelectedEntry(UStackEntry* Entry);
	UStackEntry* GetSelectedEntry() const;

	/** Returns a prebuilt Palette tab widget */
	TSharedRef<SWidget> CreatePaletteWidget();

private:
	void SetStack(UStack* InStack);

	UStack* Stack = nullptr;

	TArray<TSharedRef<FStackHandleViewModel>> HandleViewModels;

	TObjectPtr<UStackRootViewModel> RootViewModel;
	TObjectPtr<UStackSelectionViewModel> SelectionViewModel;

	TArray<TWeakObjectPtr<UStack>> Stacks;
	TWeakObjectPtr<UStack> ActiveStack;
	TWeakObjectPtr<UStackEntry> SelectedEntry;
};
