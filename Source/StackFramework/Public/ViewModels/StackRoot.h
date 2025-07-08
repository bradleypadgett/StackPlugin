#pragma once
#include "ViewModels/StackEntry.h"
#include "Definition/StackCommonTypes.h"
#include "StackRoot.generated.h"



class FStackHandleViewModel;
class FStackModuleViewModel;
class UStackEditorData;

UCLASS()
class UStackRoot : public UStackEntry
{
	GENERATED_BODY()

public:
	UStackRoot();

	void Initialize(FStackEntryContext InContext, bool bInIncludePropertiesGroup);
	virtual void FinalizeInternal() override;

	virtual bool GetCanExpand() const override;
	virtual bool GetShouldShowInStack() const override;

protected:
	virtual void RefreshChildrenInternal(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren, TArray<FStackIssue>& NewIssues) override;

private:
	void RefreshNodeChildren(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren);

	UStackEntry* GetOrCreateNodePropertiesGroup(const TArray<UStackEntry*>& CurrentChildren);

	UStackEntry* GetCurrentModuleGroup(const TArray<UStackEntry*>& CurrentChildren, FName ModuleUsageKey) const;
	UStackEntry* CreateModuleGroup(TSharedRef<FStackModuleViewModel> InModuleViewModel, EStackModuleUsage InModuleUsage, FGuid InModuleUsageId, UStackEditorData& InEditorData, FName InCategoryName, FName InSubcategoryName, FText InDisplayName, FText InToolTip);

private:
	bool bIncludePropertiesGroup;
};
