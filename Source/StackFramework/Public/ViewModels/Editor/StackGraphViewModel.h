#pragma once
#include "CoreMinimal.h"
#include "EditorUndoClient.h"



class UEdGraph;
class UStackEntry;
class FStackSystemViewModel;
class FStackObjectSelection;

/*
 * Manages a single stack-based UEdGraph — layout, selection, and interactions.
 */
class FStackGraphViewModel : public TSharedFromThis<FStackGraphViewModel>, public FEditorUndoClient
{
public:
	FStackGraphViewModel();
	virtual ~FStackGraphViewModel();

	void Initialize(TSharedRef<FStackSystemViewModel> InSystemViewModel, UEdGraph* InGraph);

	TSharedRef<FStackSystemViewModel> GetSystemViewModel() const;
	UEdGraph* GetGraph() const;

	TSharedRef<FStackObjectSelection> GetNodeSelection() const;

	void UpdateGraphNodes();

	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override { PostUndo(bSuccess); }

private:
	TWeakPtr<FStackSystemViewModel> SystemViewModel;
	TWeakObjectPtr<UEdGraph> Graph;

	TSharedPtr<FStackObjectSelection> NodeSelection;

	TArray<TWeakObjectPtr<UStackEntry>> CachedStackEntries;
};
