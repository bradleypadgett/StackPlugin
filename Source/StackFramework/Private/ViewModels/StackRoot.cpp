#include "ViewModels/StackRoot.h"
#include "ViewModels/Editor/StackHandleViewModel.h"
#include "ViewModels/Editor/StackViewModel.h"
#include "ViewModels/Editor/StackScriptViewModel.h"
#include "ViewModels/Editor/StackSystemViewModel.h"
#include "ViewModels/StackSettingsGroup.h"
#include "ViewModels/StackScriptGroup.h"
#include "ViewModels/StackGroup.h"
#include "EditorData/StackEntryEditorData.h"



#define LOCTEXT_NAMESPACE "StackRoot"

UStackRoot::UStackRoot()
{

}

void UStackRoot::Initialize(FStackEntryContext InContext, bool bInIncludeSettingsGroup)
{
	Super::Initialize(InContext, TEXT("Root"));
	bIncludeSettingsGroup = bInIncludeSettingsGroup;
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
	if (bIncludeSettingsGroup)
	{
		NewChildren.Add(GetOrCreateSettingsGroup(CurrentChildren));
	}
	
	//UStackEntryEditorData& LocalStackEntryEditorData = GetStackViewModel()->GetStackEntryEditorData();
	TSharedRef<FStackScriptViewModel> ScriptViewModel = GetStackViewModel()->GetScriptViewModel();

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
		TestEntry = CreateScriptGroup(ScriptViewModel, CompileTarget, GroupID, LocalStackEntryEditorData, ExecutionCategory, ExecutionSubCategory, EntryDisplayName, ToolTip);
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
		FStackEntryContext EntryContext(GetSystemViewModel(), GetStackViewModel(),
			FCategoryNames::Default, FSubcategoryNames::Settings,
			GetStackViewModel()->GetStackEditorData());
		SettingsGroup->Initialize(EntryContext);*/
	}
	return SettingsGroup;
}

UStackEntry* UStackRoot::CreateScriptGroup(TSharedRef<FStackScriptViewModel> InScriptViewModel, EScriptCompileTarget InScriptCompileTarget, FGuid InGroupID, UStackEntryEditorData& InStackEntryEditorData, FName InCategoryName, FName InSubcategoryName, FText InDisplayName, FText InToolTip)
{
	UStackScriptGroup* ScriptGroup = NewObject<UStackScriptGroup>(this);
	FStackEntryContext EntryContext(GetSystemViewModel(), GetStackViewModel(), InCategoryName, InSubcategoryName, InStackEntryEditorData);
	ScriptGroup->Initialize(EntryContext, InDisplayName, InToolTip, InScriptViewModel, InScriptCompileTarget, InGroupID);
	return ScriptGroup;
}

#undef LOCTEXT_NAMESPACE