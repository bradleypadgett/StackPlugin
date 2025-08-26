#pragma once
#include "CoreMinimal.h"
#include "Providers/StackSource.h"
#include "Templates/SharedPointer.h"



class UStackRoot;
class UStackEntry;
class SWidget;
class UStack;
class UStackSystem;
class UStackSystemEditorData;
class UStackRootManager;
class UStackSelectionManager;
class FStackRootManager;
class FStackHandleManager;
class FStackSystemGraphManager;
class IStackSystemProvider;

/*
 * Editor-level Manager to coordinate stack nodes, selection,
 * and inject shared features like Palette, TabManager integration, etc.
 */
class STACKFRAMEWORK_API FStackSystemManager : public TSharedFromThis<FStackSystemManager>
{
public:
	FStackSystemManager();
	virtual ~FStackSystemManager();

	void Initialize(UStackSystem& InSystem, bool bIsTemporarySystem);
	UStackSystem& GetSystem() const;
	UStackRootManager* GetSystemStackRootManager();

	void RefreshAll();
	void RefreshHandleManagers();

private:
	void ResetHandleManagers();

public:
	TSharedPtr<FStackHandleManager> GetHandleManagerFromID(const FGuid& InHandleID) const;
	TSharedPtr<FStackHandleManager> GetHandleManagerFromStack(const UStack& InStack) const;



	// TO-DO ~ remove these or integrate IStackSource into actual AddStack stuff a bit below
	void AddStackSource(TScriptInterface<IStackSource> InStackSource);
	TArray<TScriptInterface<IStackSource>> GetAllStackSources() const;
	void SetActiveStackSource(TScriptInterface<IStackSource> InStack);
	TScriptInterface<IStackSource> GetActiveStackSource() const;
	////////////////////////////////////////////////////////////////////////////////////////

	TSharedPtr<FStackHandleManager> AddEmptyStackToSystem();
	TSharedPtr<FStackHandleManager> AddStackToSystem(UStack& Stack);





public:
	void SetSelectedEntry(UStackEntry* Entry);
	UStackEntry* GetSelectedEntry() const;
	UStackSelectionManager* GetSelectionManager() const;


	/** Returns a prebuilt Palette tab widget */
	TSharedRef<SWidget> CreatePaletteWidget();

public:


	IStackSource* GetStackSource() const;
	UStackSystemEditorData& GetSystemEditorData() const;

private:
	TObjectPtr<UStackSystem> System;

	TSharedPtr<FStackSystemGraphManager> SystemGraphManager;

	// System Node
	TObjectPtr<UStackRootManager> SystemRootManager;

	void SetStackSource(TScriptInterface<IStackSource> InSource);

	TScriptInterface<IStackSource> StackSource;

	TArray<TSharedRef<FStackHandleManager>> HandleManagers;

	TObjectPtr<UStackSelectionManager> SelectionManager;

	TArray<TScriptInterface<IStackSource>> StackSources;
	TScriptInterface<IStackSource> ActiveStackSource;
	TWeakObjectPtr<UStackEntry> SelectedEntry;
};
