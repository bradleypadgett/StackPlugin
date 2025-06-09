#pragma once
#include "CoreMinimal.h"
#include "Templates/SharedPointer.h"



class UStackNode;
class UStackViewModel;
class UStackEntry;
class SWidget;

/*
 * Editor-level ViewModel to coordinate stack nodes, selection,
 * and inject shared features like Palette, TabManager integration, etc.
 */
class STACKFRAMEWORK_API FStackEditorViewModel : public TSharedFromThis<FStackEditorViewModel>
{
public:
	FStackEditorViewModel();

	void AddStackNode(UStackNode* Node);
	TArray<UStackNode*> GetAllNodes() const;

	UStackViewModel* GetViewModelForNode(UStackNode* Node) const;

	void SetActiveNode(UStackNode* Node);
	UStackNode* GetActiveNode() const;

	void SetSelectedEntry(UStackEntry* Entry);
	UStackEntry* GetSelectedEntry() const;

	/** Returns a prebuilt Palette tab widget */
	TSharedRef<SWidget> CreatePaletteWidget();

private:
	TArray<TWeakObjectPtr<UStackNode>> StackNodes;
	TWeakObjectPtr<UStackNode> ActiveNode;
	TWeakObjectPtr<UStackEntry> SelectedEntry;
};
