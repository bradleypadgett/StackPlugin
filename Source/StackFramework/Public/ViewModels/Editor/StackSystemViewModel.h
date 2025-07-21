#pragma once
#include "CoreMinimal.h"
#include "Definition/StackSource.h"
#include "Templates/SharedPointer.h"



class UStackRoot;
class UStackEntry;
class SWidget;
class UStack;
class UStackSystem;
class UStackSystemEditorData;
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

	void Initialize(TScriptInterface<IStackSource> InStackSource);

	void AddStackSource(TScriptInterface<IStackSource> InStackSource);
	TArray<TScriptInterface<IStackSource>> GetAllStackSources() const;

	UStackSelectionViewModel* GetSelectionViewModel() const;

	TSharedPtr<FStackHandleViewModel> GetHandleViewModelFromID(const FGuid& InHandleID) const;
	TSharedPtr<FStackHandleViewModel> GetHandleViewModelFromStack(const UStack& InStack) const;

	void SetActiveStackSource(TScriptInterface<IStackSource> InStack);
	TScriptInterface<IStackSource> GetActiveStackSource() const;

	void SetSelectedEntry(UStackEntry* Entry);
	UStackEntry* GetSelectedEntry() const;

	/** Returns a prebuilt Palette tab widget */
	TSharedRef<SWidget> CreatePaletteWidget();

public:


	IStackSource* GetStackSource() const;
	UStackSystemEditorData& GetSystemEditorData() const;

private:
	UStackSystemEditorData* SystemEditorData;

	void SetStackSource(TScriptInterface<IStackSource> InSource);

	TScriptInterface<IStackSource> StackSource;

	TArray<TSharedRef<FStackHandleViewModel>> HandleViewModels;

	TObjectPtr<UStackRootViewModel> RootViewModel;
	TObjectPtr<UStackSelectionViewModel> SelectionViewModel;

	TArray<TScriptInterface<IStackSource>> StackSources;
	TScriptInterface<IStackSource> ActiveStackSource;
	TWeakObjectPtr<UStackEntry> SelectedEntry;
};
