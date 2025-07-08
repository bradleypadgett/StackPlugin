#include "ViewModels/Editor/StackRootViewModel.h"
#include "ViewModels/StackRoot.h"



TArray<UStackRootViewModel::FStackRootContainer> UStackRootViewModel::GetRootContainers() const
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


void UStackRootViewModel::Initialize(UStackEntry* InRootEntry)
{
	// TO-DO ~ Flesh the heck outta this

	RootEntry = InRootEntry;
	RefreshStack();
}

void UStackRootViewModel::RefreshStack()
{
	RootEntries.Empty();

	// test hardcoded sections
	UStackRoot* SectionA = NewObject<UStackRoot>(this, FName("SectionA"));
	UStackRoot* SectionB = NewObject<UStackRoot>(this, FName("SectionB"));

	RootEntries.Add(SectionA);
	RootEntries.Add(SectionB);
}

void UStackRootViewModel::SetSearchText(const FText& NewText)
{
	SearchText = NewText;
}

UStackEntry* UStackRootViewModel::GetRootEntry()
{
	return RootEntry;
}

TArray<UStackEntry*> UStackRootViewModel::GetRootEntries()
{
	return RootEntries;
}

UStackRootViewModel::FOnExpansionChanged& UStackRootViewModel::OnExpansionChanged()
{
	return ExpansionChangedDelegate;
}

UStackRootViewModel::FOnExpansionChanged& UStackRootViewModel::OnExpansionInNodeChanged()
{
	return ExpansionInNodeChangedDelegate;
}

UStackRootViewModel::FOnStructureChanged& UStackRootViewModel::OnStructureChanged()
{
	return StructureChangedDelegate;
}