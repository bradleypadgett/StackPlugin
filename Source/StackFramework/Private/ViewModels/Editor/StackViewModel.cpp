#include "ViewModels/Editor/StackViewModel.h"
#include "ViewModels/StackEntry.h"



UStackViewModel::UStackViewModel()
{
	bIncludeEditorSections = true;
}

void UStackViewModel::Initialize(UObject* InOwnerContext, bool bInIncludeEditorSections)
{
	UE_LOG(LogTemp, Warning, TEXT("UStackViewModel::Initialize() called"));

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

	RootEntries = Children;
}

void UStackViewModel::RefreshChildrenInternal(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren)
{
	UStackEntry* Settings = NewObject<UStackEntry>(this);
	Settings->SetDisplayName(FText::FromString("System Settings"));
	NewChildren.Add(Settings);

	UStackEntry* Spawn = NewObject<UStackEntry>(this);
	Spawn->SetDisplayName(FText::FromString("System Spawn"));
	NewChildren.Add(Spawn);

	UStackEntry* Update = NewObject<UStackEntry>(this);
	Update->SetDisplayName(FText::FromString("System Update"));
	NewChildren.Add(Update);

	UStackEntry* State = NewObject<UStackEntry>(this);
	State->SetDisplayName(FText::FromString("System State"));
	NewChildren.Add(State);
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
