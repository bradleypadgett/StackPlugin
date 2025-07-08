#include "ViewModels/StackRoot.h"
#include "ViewModels/Editor/StackHandleViewModel.h"
#include "ViewModels/Editor/StackViewModel.h"
#include "ViewModels/Editor/StackModuleViewModel.h"
#include "ViewModels/Editor/StackSystemViewModel.h"
#include "ViewModels/StackSettingsGroup.h"
#include "ViewModels/StackStatelessGroup.h"
#include "ViewModels/StackStatelessModuleGroup.h"
#include "ViewModels/StackModuleGroup.h"
#include "State/StackData.h"
#include "State/StackEditorData.h"



UStackRoot::UStackRoot()
{

}

void UStackRoot::Initialize(FStackEntryContext InContext, bool bInIncludePropertiesGroup)
{
	Super::Initialize(InContext, TEXT("Root"));
	bIncludePropertiesGroup = bInIncludePropertiesGroup;
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
	RefreshNodeChildren(CurrentChildren, NewChildren);
/*
	TSharedPtr<FStackHandleViewModel> StackHandleViewModel = GetSystemViewModel()->GetStackHandleViewModelById(GetStackViewModel()->);
	if (StackHandleViewModel.IsValid())
	{
		bool bIsStateless = StackHandleViewModel->ShouldUseStatelessView();
		if (bIsStateless)
		{
			RefreshNodeStatelessChildren(CurrentChildren, NewChildren, StackHandleViewModel);
		}
	}*/
}

void UStackRoot::RefreshNodeChildren(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren)
{
	if (bIncludePropertiesGroup)
	{
		NewChildren.Add(GetOrCreateNodePropertiesGroup(CurrentChildren));
	}
}

UStackEntry* UStackRoot::GetOrCreateNodePropertiesGroup(const TArray<UStackEntry*>& CurrentChildren)
{
	UStackSettingsGroup* PropertiesGroup = FindCurrentChildOfType<UStackSettingsGroup>(CurrentChildren);
	if (PropertiesGroup == nullptr)
	{
		PropertiesGroup = NewObject<UStackSettingsGroup>(this);
		FStackEntryContext EntryContext(GetSystemViewModel(), GetStackViewModel(),
			FCategoryNames::Node, FSubcategoryNames::Settings,
			GetStackViewModel()->GetStackData().GetEditorData());
		PropertiesGroup->Initialize(EntryContext);
	}
	return PropertiesGroup;
}

UStackEntry* UStackRoot::GetCurrentModuleGroup(const TArray<UStackEntry*>& CurrentChildren, FName ModuleUsageKey) const
{
	return FindCurrentChildOfTypeByPredicate<UStackModuleGroup>(CurrentChildren, [ModuleUsageKey](const UStackModuleGroup* Group)
		{
			return Group->GetUsageKey() == ModuleUsageKey;
		});
}

UStackEntry* UStackRoot::CreateModuleGroup( TSharedRef<FStackModuleViewModel> InModuleViewModel, EStackModuleUsage InModuleUsage, FGuid InModuleUsageId, UStackEditorData& InEditorData, FName InCategoryName, FName InSubcategoryName, FText InDisplayName, FText InToolTip)
{
	UStackModuleGroup* ModuleGroup = NewObject<UStackModuleGroup>(this);
	FStackEntryContext Context(GetSystemViewModel(), GetStackViewModel(), InCategoryName, InSubcategoryName, InEditorData);
	ModuleGroup->Initialize(Context, InDisplayName, InToolTip, InModuleViewModel, InModuleUsage, InModuleUsageId);
	return ModuleGroup;
}
