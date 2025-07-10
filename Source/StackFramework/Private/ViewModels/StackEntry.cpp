#include "ViewModels/StackEntry.h"
#include "State/StackViewState.h"



const FName UStackEntry::FCategoryNames::Default = TEXT("Default");
const FName UStackEntry::FCategoryNames::Node = TEXT("Node");

const FName UStackEntry::FSubcategoryNames::Default = TEXT("Default");
const FName UStackEntry::FSubcategoryNames::Settings = TEXT("Settings");

UStackEntry::UStackEntry()
{

}

void UStackEntry::Initialize(FStackEntryContext InStackEntryContext, FString InStackViewStateKey)
{
	SystemViewModel = InStackEntryContext.SystemViewModel;
	StackViewModel = InStackEntryContext.StackViewModel;
	CategoryName = InStackEntryContext.CategoryName;
	SubcategoryName = InStackEntryContext.SubcategoryName;
	StackViewState = InStackEntryContext.StackViewState;

	StackViewStateKey = InStackViewStateKey;
}


bool UStackEntry::IsFinalized() const
{
	return bIsFinalized;
}

void UStackEntry::FinalizeInternal()
{
	bIsFinalized = true;
}

FText UStackEntry::GetDisplayName() const
{
	return !DisplayName.IsEmpty() ? DisplayName : FText::FromString(TEXT("<Unnamed>"));
}

UStackViewState& UStackEntry::GetStackViewState() const
{
	checkf(StackViewState, TEXT("StackState is nullptr — check finalized state first"));
	return *StackViewState;
}

FString UStackEntry::GetStackViewStateKey() const
{
	return StackViewStateKey;
}

FText UStackEntry::GetTooltipText() const
{
	return FText();
}

bool UStackEntry::GetCanExpand() const
{
	return Children.Num() > 0;
}

bool UStackEntry::GetCanExpandInNode() const
{
	return false;
}

bool UStackEntry::GetIsExpandedInNode() const
{
	if (!bIsExpandedInNodeCache.IsSet() && StackViewState != nullptr)
	{
		bIsExpandedInNodeCache = StackViewState->GetIsExpandedInNode(GetStackViewStateKey(), false);
	}
	return bIsExpandedInNodeCache.Get(false);
}

void UStackEntry::SetIsExpandedInNode(bool bInExpanded)
{
	if (StackViewState && GetCanExpandInNode())
	{
		StackViewState->SetIsExpandedInNode(GetStackViewStateKey(), bInExpanded);
	}
	bIsExpandedInNodeCache.Reset();
	ExpansionInNodeChangedDelegate.Broadcast();
}

bool UStackEntry::GetIsEnabled() const
{
	return true;
}

bool UStackEntry::GetOwnerIsEnabled() const
{
	return bOwnerIsEnabled;
}

int32 UStackEntry::GetIndentLevel() const
{
	return IndentLevel;
}

bool UStackEntry::GetShouldShowInStack() const
{
	return true;
}

bool UStackEntry::HasIssuesOrAnyChildHasIssues() const
{
	return false;
}

int32 UStackEntry::GetTotalNumberOfInfoIssues() const
{
	return 0;
}

int32 UStackEntry::GetTotalNumberOfWarningIssues() const
{
	return 0;
}

int32 UStackEntry::GetTotalNumberOfErrorIssues() const
{
	return 0;
}

const TArray<UStackEntry::FStackIssue>& UStackEntry::GetIssues() const
{
	return StackIssues;
}

void UStackEntry::RefreshStackChildren(const TArray<UStackEntry*>& /*CurrentChildren*/, TArray<UStackEntry*>& /*OutNewChildren*/, TArray<FStackIssue>& NewIssues)
{

}

void UStackEntry::RefreshChildren()
{
	TArray<UStackEntry*> NewChildren;
	TArray<FStackIssue> NewStackIssues;
	RefreshStackChildren(Children, NewChildren, NewStackIssues);

	Children.Empty();
	for (UStackEntry* Entry : NewChildren)
	{
		Children.Add(Entry);
	}
}

const TArray<UStackEntry*>& UStackEntry::GetChildren() const
{
	return Children;
}

int32 UStackEntry::GetChildIndentLevel() const
{
	return GetIndentLevel();
}

const TArray<UStackEntry*>& UStackEntry::GetFilteredChildren(TArray<UStackEntry*>& OutFilteredChildren) const
{
	return GetChildren(); // TO-DO ~ Filter
}

void UStackEntry::GetFilteredChildrenOfTypes(TArray<UStackEntry*>& OutFilteredChildren, const TSet<UClass*>& AllowedClasses, bool bRecursive) const
{
	for (UStackEntry* Child : GetChildren())
	{
		for (const UClass* Class : AllowedClasses)
		{
			if (Child->IsA(Class))
			{
				OutFilteredChildren.Add(Child);
				break;
			}
		}

		if (bRecursive)
		{
			Child->GetFilteredChildrenOfTypes(OutFilteredChildren, AllowedClasses, bRecursive);
		}
	}
}


TSharedRef<FStackSystemViewModel> UStackEntry::GetSystemViewModel() const
{
	TSharedPtr<FStackSystemViewModel> PinnedSystemViewModel = SystemViewModel.Pin();
	checkf(PinnedSystemViewModel.IsValid(), TEXT("Base stack entry not initialized or system view model was already deleted."));
	return PinnedSystemViewModel.ToSharedRef();
}

TSharedPtr<FStackSystemViewModel> UStackEntry::GetSystemViewModelPtr() const
{
	return SystemViewModel.Pin();
}

TSharedPtr<FStackViewModel> UStackEntry::GetStackViewModel() const
{
	return StackViewModel.Pin();
}

UStackEntry::FOnExpansionChanged& UStackEntry::OnExpansionChanged()
{
	return ExpansionChangedDelegate;
}

UStackEntry::FOnExpansionChanged& UStackEntry::OnExpansionInNodeChanged()
{
	return ExpansionInNodeChangedDelegate;
}

UStackEntry::FOnStructureChanged& UStackEntry::OnStructureChanged()
{
	return StructureChangedDelegate;
}

void UStackEntry::ChildStructureChangedInternal()
{
	return;
}