#include "ViewModels/StackEntry.h"
#include "EditorData/StackRootEditorData.h"



const FName UStackEntry::FCategoryNames::Default = TEXT("Default");
const FName UStackEntry::FCategoryNames::System = TEXT("System");

const FName UStackEntry::FSubcategoryNames::Default = TEXT("Default");
const FName UStackEntry::FSubcategoryNames::Settings = TEXT("Settings");

UStackEntry::UStackEntry()
{

}

void UStackEntry::Initialize(FStackEntryContext InStackEntryContext, FString InEntryEditorDataKey)
{
	SystemManager = InStackEntryContext.SystemManager;
	StackManager = InStackEntryContext.StackManager;
	CategoryName = InStackEntryContext.CategoryName;
	SubcategoryName = InStackEntryContext.SubcategoryName;
	RootEditorData = InStackEntryContext.RootEditorData;

	EntryEditorDataKey = InEntryEditorDataKey;
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

UStackRootEditorData& UStackEntry::GetRootEditorData() const
{
	checkf(RootEditorData, TEXT("StackState is nullptr — check finalized state first"));
	return *RootEditorData;
}

FString UStackEntry::GetEntryEditorDataKey() const
{
	return EntryEditorDataKey;
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
	if (!bIsExpandedInNodeCache.IsSet() && RootEditorData != nullptr)
	{
		bIsExpandedInNodeCache = RootEditorData->GetIsExpandedInNode(GetEntryEditorDataKey(), false);
	}
	return bIsExpandedInNodeCache.Get(false);
}

void UStackEntry::SetIsExpandedInNode(bool bInExpanded)
{
	if (RootEditorData && GetCanExpandInNode())
	{
		RootEditorData->SetIsExpandedInNode(GetEntryEditorDataKey(), bInExpanded);
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
	return FStackEntryContext(GetSystemManager(), GetStackManager(), GetCategory(), GetSubcategory(), GetRootEditorData());
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


TSharedRef<FStackSystemManager> UStackEntry::GetSystemManager() const
{
	TSharedPtr<FStackSystemManager> PinnedSystemManager = SystemManager.Pin();
	checkf(PinnedSystemManager.IsValid(), TEXT("Base stack entry not initialized or system view model was already deleted."));
	return PinnedSystemManager.ToSharedRef();
}

TSharedPtr<FStackSystemManager> UStackEntry::GetSystemManagerPtr() const
{
	return SystemManager.Pin();
}

TSharedPtr<FStackManager> UStackEntry::GetStackManager() const
{
	return StackManager.Pin();
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