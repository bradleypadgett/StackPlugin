#include "ViewModels/StackEntry.h"



UStackEntry::UStackEntry()
{

}

void UStackEntry::RefreshChildren()
{
	TArray<UStackEntry*> NewChildren;
	RefreshChildrenInternal(Children, NewChildren);

	Children.Empty();
	for (UStackEntry* Entry : NewChildren)
	{
		Children.Add(Entry);
	}
}

void UStackEntry::RefreshChildrenInternal(const TArray<UStackEntry*>& /*CurrentChildren*/, TArray<UStackEntry*>& /*OutNewChildren*/)
{

}

FText UStackEntry::GetDisplayName() const
{
	return FText::FromString(TEXT("Untitled Entry"));
}

bool UStackEntry::GetCanExpand() const
{
	return Children.Num() > 0;
}

bool UStackEntry::GetShouldShowInStack() const
{
	return true;
}

const TArray<UStackEntry*>& UStackEntry::GetChildren() const
{
	return Children;
}
