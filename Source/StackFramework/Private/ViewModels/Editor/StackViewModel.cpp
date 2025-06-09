#include "ViewModels/Editor/StackViewModel.h"
#include "ViewModels/StackEntry.h"



UStackViewModel::UStackViewModel()
{
	bIncludeEditorSections = true;
}

void UStackViewModel::Initialize(UObject* InOwnerContext, bool bInIncludeEditorSections)
{
	OwnerContext = InOwnerContext;
	bIncludeEditorSections = bInIncludeEditorSections;

	RefreshChildren();
}

UStackSelectionViewModel* UStackViewModel::GetSelectionViewModel() const
{
	return SelectionViewModel;
}

const TArray<UStackEntry*>& UStackViewModel::GetRootEntries() const
{
	return RootEntries;
}

void UStackViewModel::RefreshChildren()
{
	TArray<UStackEntry*> NewChildren;
	RefreshChildrenInternal(Children, NewChildren);

	Children.Empty();
	for (UStackEntry* Entry : NewChildren)
	{
		Children.Add(Entry);
	}
}

void UStackViewModel::RefreshChildrenInternal(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren)
{
	// TODO: Subclass override
}

UStackEntry* UStackViewModel::GetOrCreateGroup(FName GroupID, const TArray<UStackEntry*>& CurrentChildren)
{
	for (UStackEntry* Entry : CurrentChildren)
	{
		if (Entry && Entry->GetFName() == GroupID)
		{
			return Entry;
		}
	}

	UStackEntry* NewGroup = NewObject<UStackEntry>(this, GroupID);
	return NewGroup;
}
