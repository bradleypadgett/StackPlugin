#include "ViewModels/StackSettingsGroup.h"
#include "ViewModels/StackObject.h"
#include "ViewModels/StackEntry.h"
#include "ViewModels/StackGroup.h"
#include "ViewModels/StackScriptGroup.h"



#define LOCTEXT_NAMESPACE "StackSettings"

UStackSettingsGroup::UStackSettingsGroup()
{

}

void UStackSettingsGroup::Initialize(FStackEntryContext InEntryContext)
{
	FText InDisplayName = LOCTEXT("StackSettingsGroupName", "Settings");
	FText Tooltip = LOCTEXT("StackSettingsTooltip", "Settings for the Stack");
	AddUtilities = MakeShared<FStackSettingsAddUtilities>(this, FStackSettingsAddUtilities::FOnItemAdded::CreateUObject(this, &UStackSettingsGroup::OnGroupAdded));
	Super::Initialize(InEntryContext, InDisplayName, Tooltip, AddUtilities.Get());
}

void UStackSettingsGroup::RefreshChildrenInternal(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren, TArray<FStackIssue>& NewIssues)
{
	if (!SettingsItem)
	{
		SettingsItem = NewObject<UStackSettingsItem>(this);
		SettingsItem->Initialize(GetDefaultEntryContext());
	}
	NewChildren.Add(SettingsItem);

	for (UStackScriptGroup* Group : AddedGroups)
	{
		NewChildren.Add(Group);
	}

	Super::RefreshChildrenInternal(CurrentChildren, NewChildren, NewIssues);
}

void UStackSettingsGroup::OnGroupAdded(UStackScriptGroup* NewGroup)
{
	AddedGroups.Add(NewGroup);
	RefreshChildren();
}

void UStackSettingsItem::Initialize(FStackEntryContext InContext)
{
	return;
}


void UStackSettingsItem::RefreshChildrenInternal(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren, TArray<FStackIssue>& NewIssues)
{
	return;
}

void FStackSettingsAddUtilities::GenerateAddActions(TArray<TSharedRef<FStackAddAction>>& OutActions) const
{
	OutActions.Add(MakeShared<FStackAddAction>(
		FText::FromString("Add Settings Object"),
		FText::FromString("Creates a new settings data object."),
		FText::FromString("settings create add new")
	));
}

void FStackSettingsAddUtilities::ExecuteAddAction(TSharedRef<FStackAddAction> Action, int32 TargetIndex)
{
	AddItemDirectly();
}

void FStackSettingsAddUtilities::AddItemDirectly()
{
	if (UStackSettingsGroup* Group = OwningGroup.Get())
	{
		UStackScriptGroup* NewGroup = NewObject<UStackScriptGroup>(Group);
		OnItemAdded.ExecuteIfBound(NewGroup);
	}
}


#undef LOCTEXT_NAMESPACE
