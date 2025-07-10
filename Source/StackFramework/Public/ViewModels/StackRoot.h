#pragma once
#include "ViewModels/StackEntry.h"
#include "Definition/StackCommonTypes.h"
#include "StackRoot.generated.h"



class FStackHandleViewModel;
class FStackModuleViewModel;
class UStackViewState;

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
	virtual void RefreshStackChildren(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren, TArray<FStackIssue>& NewIssues) override;

private:

	UStackEntry* GetOrCreateStackSettingsGroup(const TArray<UStackEntry*>& CurrentChildren);

	UStackEntry* GetCurrentModuleGroup(const TArray<UStackEntry*>& CurrentChildren, FName ModuleUsageKey) const;
	UStackEntry* CreateModuleGroup(TSharedRef<FStackModuleViewModel> InModuleViewModel, EStackModuleUsage InModuleUsage, FGuid InModuleUsageId, UStackViewState& InStackViewState, FName InCategoryName, FName InSubcategoryName, FText InDisplayName, FText InToolTip);

private:
	bool bIncludeSettingsGroup;
};
