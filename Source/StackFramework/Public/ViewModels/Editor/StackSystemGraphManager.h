#pragma once
#include "CoreMinimal.h"
#include "EditorUndoClient.h"



class UEdGraph;
class UStackEntry;
class FStackSystemManager;
class FStackObjectSelection;

/*
 * Manages a single stack-based UEdGraph — layout, selection, and interactions.
 */
class FStackSystemGraphManager : public TSharedFromThis<FStackSystemGraphManager>, public FEditorUndoClient
{
public:
	FStackSystemGraphManager();
	virtual ~FStackSystemGraphManager();

	void Initialize(TSharedRef<FStackSystemManager> InSystemManager);

	TSharedRef<FStackSystemManager> GetSystemManager() const;
	UEdGraph* GetGraph() const;

	TSharedRef<FStackObjectSelection> GetNodeSelection() const;

	void UpdateSystemGraphNodes();

	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override { PostUndo(bSuccess); }

private:
	TWeakPtr<FStackSystemManager> SystemManager;
	TWeakObjectPtr<UEdGraph> SystemGraph;

	TSharedPtr<FStackObjectSelection> NodeSelection;

	TArray<TWeakObjectPtr<UStackEntry>> CachedStackEntries;
};
