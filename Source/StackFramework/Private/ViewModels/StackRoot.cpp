#include "ViewModels/StackRoot.h"
#include "ViewModels/Editor/StackHandleViewModel.h"
#include "ViewModels/Editor/StackViewModel.h"
#include "ViewModels/Editor/StackModuleViewModel.h"
#include "ViewModels/Editor/StackSystemViewModel.h"
#include "ViewModels/StackSettingsGroup.h"
#include "ViewModels/StackStatelessGroup.h"
#include "ViewModels/StackStatelessModuleGroup.h"
#include "ViewModels/StackModuleGroup.h"
#include "State/StackViewState.h"



UStackRoot::UStackRoot()
{

}

void UStackRoot::Initialize(FStackEntryContext InContext, bool bInIncludePropertiesGroup)
{
	Super::Initialize(InContext, TEXT("Root"));
	bIncludeSettingsGroup = bInIncludePropertiesGroup;
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

void UStackRoot::RefreshStackChildren(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren, TArray<FStackIssue>& NewIssues)
{
	if (bIncludeSettingsGroup)
	{
		NewChildren.Add(GetOrCreateStackSettingsGroup(CurrentChildren));
	}
	/*
	UStackEditorState* StackEditorState = GetStackViewModel()->GetStackEditorState();
	for (UStackModule* Module : StackEditorState->GetModules())
	{
		const FGuid ModuleId = FGuid::NewGuid(); // Placeholder until real ID
		const FText DisplayName = FText::FromString(TEXT("Module Group"));
		const FText ToolTip = FText::FromString(TEXT("A user-added module group"));

		UStackModuleGroup* Group = NewObject<UStackModuleGroup>(this);
		
		FStackEntryContext EntryContext(
			GetSystemViewModel(),
			GetStackViewModel(),
			FCategoryNames::Default,
			FSubcategoryNames::Default,
			GetStackViewModel()->GetStackState());

		Group->Initialize(EntryContext, DisplayName, ToolTip, MakeShared<FStackModuleViewModel>(), EStackModuleUsage::Standard, ModuleId);

		NewChildren.Add(Group);
	}*/

}

UStackEntry* UStackRoot::GetOrCreateStackSettingsGroup(const TArray<UStackEntry*>& CurrentChildren)
{
	UStackSettingsGroup* SettingsGroup = FindCurrentChildOfType<UStackSettingsGroup>(CurrentChildren);
	if (SettingsGroup == nullptr)
	{
		SettingsGroup = NewObject<UStackSettingsGroup>(this);
		FStackEntryContext EntryContext(GetSystemViewModel(), GetStackViewModel(),
			FCategoryNames::Node, FSubcategoryNames::Settings,
			GetStackViewModel()->GetStackViewState());
		SettingsGroup->Initialize(EntryContext);
	}
	return SettingsGroup;
}

UStackEntry* UStackRoot::GetCurrentModuleGroup(const TArray<UStackEntry*>& CurrentChildren, FName ModuleUsageKey) const
{
	return FindCurrentChildOfTypeByPredicate<UStackModuleGroup>(CurrentChildren, [ModuleUsageKey](const UStackModuleGroup* Group)
		{
			return Group->GetUsageKey() == ModuleUsageKey;
		});
}

UStackEntry* UStackRoot::CreateModuleGroup( TSharedRef<FStackModuleViewModel> InModuleViewModel, EStackModuleUsage InModuleUsage, FGuid InModuleUsageId, UStackViewState& InStackViewState, FName InCategoryName, FName InSubcategoryName, FText InDisplayName, FText InToolTip)
{
	UStackModuleGroup* ModuleGroup = NewObject<UStackModuleGroup>(this);
	FStackEntryContext Context(GetSystemViewModel(), GetStackViewModel(), InCategoryName, InSubcategoryName, InStackViewState);
	ModuleGroup->Initialize(Context, InDisplayName, InToolTip, InModuleViewModel, InModuleUsage, InModuleUsageId);
	return ModuleGroup;
}
