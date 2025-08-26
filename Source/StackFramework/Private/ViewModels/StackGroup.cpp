#include "ViewModels/StackGroup.h"
//#include "ViewModels/StackGroupFooter.h"
#include "ViewModels/StackEntry.h"
#include "Utilities/StackCommonTypes.h"

#define LOCTEXT_NAMESPACE "StackGroup"

void UStackGroup::Initialize(FStackEntryContext InContext, FText InDisplayName, FText InToolTip, IStackGroupAddUtilities* InAddUtilities)
{
	AddUtilities = InAddUtilities;
	GroupDisplayName = InDisplayName;
	GroupToolTip = InToolTip;

	Super::Initialize(InContext, InDisplayName.ToString());
}

EScriptCompileTarget UStackGroup::GetScriptCompileTarget() const
{
	return ScriptCompileTarget;
}

FGuid UStackGroup::GetGroupID() const
{
	return GroupID;
}



FText UStackGroup::GetDisplayName() const
{
	return GroupDisplayName;
}

FText UStackGroup::GetTooltipText() const
{
	return GroupToolTip;
}

void UStackGroup::SetDisplayName(FText InDisplayName)
{
	GroupDisplayName = InDisplayName;
}

IStackGroupAddUtilities* UStackGroup::GetAddUtilities() const
{
	return AddUtilities;
}

int32 UStackGroup::GetChildIndentLevel() const
{
	return GetIndentLevel();
}

void UStackGroup::RefreshChildrenInternal(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren, TArray<FStackIssue>& NewIssues)
{
	NewChildren.Empty();
}

void UStackGroup::ChildStructureChangedInternal()
{
	RecursiveStackIssuesCount.Reset();
	HighestIssueSeverity.Reset();
}

bool UStackGroup::FilterChildrenWithIssues(const UStackEntry& Child) const
{
	return false;
}

#undef LOCTEXT_NAMESPACE
