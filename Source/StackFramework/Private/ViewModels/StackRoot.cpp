#include "ViewModels/StackRoot.h"
#include "ViewModels/Editor/StackHandleManager.h"
#include "ViewModels/Editor/StackManager.h"
#include "ViewModels/Editor/StackScriptManager.h"
#include "ViewModels/Editor/StackSystemManager.h"
#include "ViewModels/StackSettingsGroup.h"
#include "ViewModels/StackScriptGroup.h"
#include "ViewModels/StackGroup.h"
#include "EditorData/StackRootEditorData.h"



#define LOCTEXT_NAMESPACE "StackRoot"

UStackRoot::UStackRoot()
{

}

void UStackRoot::Initialize(FStackEntryContext InContext, bool bIncludeSettingsGroup)
{
	Super::Initialize(InContext, TEXT("Root"));
	bSettingsGroupEnabled = bIncludeSettingsGroup;
}

void UStackRoot::FinalizeInternal()
{
	Super::FinalizeInternal();
}

bool UStackRoot::GetCanExpand() const
{
	return false;
}

bool UStackRoot::GetShouldShowInStack() const
{
	return false;
}

void UStackRoot::RefreshChildrenInternal(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren, TArray<FStackIssue>& NewIssues)
{
	if (bSettingsGroupEnabled)
	{
		NewChildren.Add(GetOrCreateSettingsGroup(CurrentChildren));
	}
	
	//UStackRootEditorData& RootEditorData = GetStackManager()->GetRootEditorData();
	
	// might remove this later
	//TSharedRef<FStackScriptManager> ScriptManager = GetStackManager()->GetScriptManager();

	/*
	UStackEntry* TestEntry = GetCurrentGroupByCompileTarget(CurrentChildren, EScriptCompileTarget::Default, FGuid());
	if (TestEntry == nullptr)
	{
		EScriptCompileTarget CompileTarget = EScriptCompileTarget::Default;
		FGuid GroupID = FGuid();
		FName ExecutionCategory = FCategoryNames::Default;
		FName ExecutionSubCategory = FSubcategoryNames::Default;
		FText EntryDisplayName = LOCTEXT("TestGroupName", "testin'");
		FText ToolTip = LOCTEXT("TestGroupTooltip", "hopefully this shows up lol");
		TestEntry = CreateScriptGroup(ScriptManager, CompileTarget, GroupID, LocalRootEditorData, ExecutionCategory, ExecutionSubCategory, EntryDisplayName, ToolTip);
	}
	NewChildren.Add(TestEntry);*/
}


UStackEntry* UStackRoot::GetCurrentGroupByCompileTarget(const TArray<UStackEntry*>& CurrentChildren, EScriptCompileTarget InScriptCompileTarget, FGuid InGroupID) const
{
	return FindCurrentChildOfTypeByPredicate<UStackGroup>(
		CurrentChildren, [InScriptCompileTarget, InGroupID](UStackGroup* Group) {
			return Group->GetScriptCompileTarget() == InScriptCompileTarget && Group->GetGroupID() == InGroupID; });
}

UStackEntry* UStackRoot::GetCurrentGroupByCategory(const TArray<UStackEntry*>& CurrentChildren, FName InCategory, FName InSubcategory, FGuid InGroupID) const
{
	return FindCurrentChildOfTypeByPredicate<UStackGroup>(
		CurrentChildren,
		[InCategory, InSubcategory, InGroupID](UStackGroup* Group)
		{
			return Group->GetCategory() == InCategory &&
				Group->GetSubcategory() == InSubcategory &&
				Group->GetGroupID() == InGroupID;
		});
}

UStackEntry* UStackRoot::GetOrCreateSettingsGroup(const TArray<UStackEntry*>& CurrentChildren)
{
	UStackSettingsGroup* SettingsGroup = FindCurrentChildOfType<UStackSettingsGroup>(CurrentChildren);
	if (SettingsGroup == nullptr)
	{
	/*	SettingsGroup = NewObject<UStackSettingsGroup>(this);
		FStackEntryContext EntryContext(GetSystemManager(), GetStackManager(),
			FCategoryNames::Default, FSubcategoryNames::Settings,
			GetStackManager()->GetStackEditorData());
		SettingsGroup->Initialize(EntryContext);*/
	}
	return SettingsGroup;
}

UStackEntry* UStackRoot::CreateScriptGroup(TSharedRef<FStackScriptManager> InScriptManager, EScriptCompileTarget InScriptCompileTarget, FGuid InGroupID, UStackRootEditorData& InRootEditorData, FName InCategoryName, FName InSubcategoryName, FText InDisplayName, FText InToolTip)
{
	UStackScriptGroup* ScriptGroup = NewObject<UStackScriptGroup>(this);
	FStackEntryContext EntryContext(GetSystemManager(), GetStackManager(), InCategoryName, InSubcategoryName, InRootEditorData);
	ScriptGroup->Initialize(EntryContext, InDisplayName, InToolTip, InScriptManager, InScriptCompileTarget, InGroupID);
	return ScriptGroup;
}

#undef LOCTEXT_NAMESPACE