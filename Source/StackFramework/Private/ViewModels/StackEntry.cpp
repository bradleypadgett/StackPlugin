#include "ViewModels/StackEntry.h"
#include "EditorData/StackEntryEditorData.h"



const FName UStackEntry::FCategoryNames::Default = TEXT("Default");
const FName UStackEntry::FCategoryNames::System = TEXT("System");

const FName UStackEntry::FSubcategoryNames::Default = TEXT("Default");
const FName UStackEntry::FSubcategoryNames::Settings = TEXT("Settings");

UStackEntry::UStackEntry()
{

}

void UStackEntry::Initialize(FStackEntryContext InStackEntryContext, FString InStackEntryEditorDataKey)
{
	SystemViewModel = InStackEntryContext.SystemViewModel;
	StackViewModel = InStackEntryContext.StackViewModel;
	CategoryName = InStackEntryContext.CategoryName;
	SubcategoryName = InStackEntryContext.SubcategoryName;
	StackEntryEditorData = InStackEntryContext.StackEntryEditorData;

	StackEntryEditorDataKey = InStackEntryEditorDataKey;
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

UStackEntryEditorData& UStackEntry::GetStackEntryEditorData() const
{
	checkf(StackEntryEditorData, TEXT("StackState is nullptr — check finalized state first"));
	return *StackEntryEditorData;
}

FString UStackEntry::GetStackEntryEditorDataKey() const
{
	return StackEntryEditorDataKey;
}

FText UStackEntry::GetTooltipText() const
{
	return FText();
}

UObject* UStackEntry::GetDisplayedObject() const
{
	return nullptr;
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
	if (!bIsExpandedInNodeCache.IsSet() && StackEntryEditorData != nullptr)
	{
		bIsExpandedInNodeCache = StackEntryEditorData->GetIsExpandedInNode(GetStackEntryEditorDataKey(), false);
	}
	return bIsExpandedInNodeCache.Get(false);
}

void UStackEntry::SetIsExpandedInNode(bool bInExpanded)
{
	if (StackEntryEditorData && GetCanExpandInNode())
	{
		StackEntryEditorData->SetIsExpandedInNode(GetStackEntryEditorDataKey(), bInExpanded);
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

UStackEntry::FStackEntryContext UStackEntry::GetDefaultEntryContext() const
{
	return FStackEntryContext(GetSystemViewModel(), GetStackViewModel(), GetCategory(), GetSubcategory(), GetStackEntryEditorData());
}

void UStackEntry::RefreshChildrenInternal(const TArray<UStackEntry*>& /*CurrentChildren*/, TArray<UStackEntry*>& /*OutNewChildren*/, TArray<FStackIssue>& NewIssues)
{

}

void UStackEntry::RefreshChildren()
{
	TArray<UStackEntry*> NewChildren;
	TArray<FStackIssue> NewStackIssues;
	RefreshChildrenInternal(Children, NewChildren, NewStackIssues);

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