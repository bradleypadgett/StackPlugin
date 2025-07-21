#pragma once
#include "ViewModels/StackEntry.h"
#include "Definition/StackCommonTypes.h"
#include "StackRoot.generated.h"



class FStackHandleViewModel;
class FStackScriptViewModel;
class UStackEntryEditorData;

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

	UStackEntry* GetCurrentGroupByCompileTarget(const TArray<UStackEntry*>& CurrentChildren, EScriptCompileTarget InScriptCompileTarget, FGuid InGroupID) const;
	UStackEntry* GetCurrentGroupByCategory(const TArray<UStackEntry*>& CurrentChildren, FName InCategory, FName InSubcategory, FGuid InGroupID) const;

	UStackEntry* GetOrCreateSettingsGroup(const TArray<UStackEntry*>& CurrentChildren);

	UStackEntry* CreateScriptGroup(TSharedRef<FStackScriptViewModel> InScriptViewModel, EScriptCompileTarget InScriptCompileTarget, FGuid InGroupID, UStackEntryEditorData& InStackEntryEditorData, FName InCategoryName, FName InSubcategoryName, FText InDisplayName, FText InToolTip);

private:
	bool bIncludeSettingsGroup;
};
