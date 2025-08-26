#include "ViewModels/Editor/StackRootManager.h"
#include "ViewModels/Editor/StackSystemManager.h"
#include "ViewModels/Editor/StackHandleManager.h"
#include "ViewModels/Editor/StackManager.h"
#include "ViewModels/StackEntry.h"
#include "ViewModels/StackRoot.h"
#include "EditorData/StackSystemEditorData.h"
#include "EditorData/StackRootEditorData.h"
#include "EditorData/StackEditorData.h"



TArray<UStackRootManager::FStackRootContainer> UStackRootManager::GetRootContainers() const
{
	TArray<FStackRootContainer> ViewModels;
	for (UStackEntry* Root : RootEntries)
	{
		if (Root)
		{
			ViewModels.Add(FStackRootContainer(Root, Root->GetDisplayName()));
		}
	}
	return ViewModels;
}


void UStackRootManager::InitializeStack(TSharedPtr<FStackSystemManager> InSystemManager, TSharedPtr<FStackHandleManager> InHandleManager)
{
	Reset();
	if (InSystemManager.IsValid()) 
	{
		UStackRoot* NewStackRoot = NewObject<UStackRoot>(this);
		TSharedPtr<FStackManager> NewStackManager = TSharedPtr<FStackManager>();

		if (InHandleManager.IsValid())
		{
			NewStackManager = InHandleManager->GetStackManager();
			if (NewStackManager.IsValid()) NewStackManager->OnHandleRemoved().AddUObject(this, &UStackRootManager::HandleRemoved);
		}

		UStackEntry::FStackEntryContext DummyRootEntryContext(
			InSystemManager.ToSharedRef(),
			NewStackManager,
			UStackEntry::FCategoryNames::Default,
			UStackEntry::FSubcategoryNames::Default,
			InSystemManager->GetSystemEditorData().GetSystemRootEditorData()
		);

		NewStackRoot->Initialize(DummyRootEntryContext, true /* bIncludeOtherStuff */);
		NewStackRoot->RefreshChildren();

		//NewStackRoot->OnStructureChanged().AddUObject(this, &UStackRootManager::HandleStructureChanged);
		//NewStackRoot->OnExpansionChanged().AddUObject(this, &UStackRootManager::HandleExpansionChanged);
		//NewStackRoot->OnRequestFullRefresh().AddUObject(this, &UStackRootManager::RequestFullRefresh);

		// 6. Assign to RootEntry
		RootEntry = NewStackRoot;
		RootEntries.Add(NewStackRoot);

		//StructureChangedDelegate.Broadcast(/* flags */);
	}

	SystemManager = InSystemManager;
	StackHandleManager = InHandleManager;
}

void UStackRootManager::InitializeStack(UStackEntry* InRootEntry)
{
	Reset();
	RootEntry = InRootEntry;

	// TO-DO ~ Delegates
	
	//RootEntry->Initialize();

	RefreshStack();
}

void UStackRootManager::HandleRemoved()
{
	//RootEntry->RefreshStack();
}

void UStackRootManager::RefreshStack()
{

}

void UStackRootManager::SetSearchText(const FText& NewText)
{
	SearchText = NewText;
}

UStackEntry* UStackRootManager::GetRootEntry()
{
	return RootEntry;
}

TArray<UStackEntry*> UStackRootManager::GetRootEntries()
{
	return RootEntries;
}

UStackRootManager::FOnExpansionChanged& UStackRootManager::OnExpansionChanged()
{
	return ExpansionChangedDelegate;
}

UStackRootManager::FOnExpansionChanged& UStackRootManager::OnExpansionInNodeChanged()
{
	return ExpansionInNodeChangedDelegate;
}

UStackRootManager::FOnStructureChanged& UStackRootManager::OnStructureChanged()
{
	return StructureChangedDelegate;
}

void UStackRootManager::Reset()
{

}