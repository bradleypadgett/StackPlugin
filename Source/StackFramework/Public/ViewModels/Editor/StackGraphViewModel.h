#pragma once
#include "CoreMinimal.h"
#include "EditorUndoClient.h"



class UEdGraph;
class UStackEntry;
class FStackEditorViewModel;
class FStackObjectSelection;

/*
 * Manages a single stack-based UEdGraph — layout, selection, and interactions.
 */
class FStackGraphViewModel : public TSharedFromThis<FStackGraphViewModel>, public FEditorUndoClient
{
public:
	FStackGraphViewModel();
	virtual ~FStackGraphViewModel();

	void Initialize(TSharedRef<FStackEditorViewModel> InEditorViewModel, UEdGraph* InGraph);

	TSharedRef<FStackEditorViewModel> GetEditorViewModel() const;
	UEdGraph* GetGraph() const;

	TSharedRef<FStackObjectSelection> GetNodeSelection() const;

	void UpdateGraphNodes();

	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override { PostUndo(bSuccess); }

private:
	TWeakPtr<FStackEditorViewModel> EditorViewModel;
	TWeakObjectPtr<UEdGraph> Graph;

	TSharedPtr<FStackObjectSelection> NodeSelection;

	TArray<TWeakObjectPtr<UStackEntry>> CachedStackEntries;
};
