#pragma once
#include "ViewModels/StackEntry.h"
#include "Utilities/StackCommonTypes.h"
#include "StackRoot.generated.h"



class FStackHandleManager;
class FStackScriptManager;
class UStackRootEditorData;

UCLASS()
class UStackRoot : public UStackEntry
{
	GENERATED_BODY()

public:
	UStackRoot();

	void Initialize(FStackEntryContext InContext, bool bIncludeSettingsGroup);
	virtual void FinalizeInternal() override;

	virtual bool GetCanExpand() const override;
	virtual bool GetShouldShowInStack() const override;

protected:
	virtual void RefreshChildrenInternal(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren, TArray<FStackIssue>& NewIssues) override;

private:

	UStackEntry* GetCurrentGroupByCompileTarget(const TArray<UStackEntry*>& CurrentChildren, EScriptCompileTarget InScriptCompileTarget, FGuid InGroupID) const;
	UStackEntry* GetCurrentGroupByCategory(const TArray<UStackEntry*>& CurrentChildren, FName InCategory, FName InSubcategory, FGuid InGroupID) const;

	UStackEntry* GetOrCreateSettingsGroup(const TArray<UStackEntry*>& CurrentChildren);

	UStackEntry* CreateScriptGroup(TSharedRef<FStackScriptManager> InScriptManager, EScriptCompileTarget InScriptCompileTarget, FGuid InGroupID, UStackRootEditorData& InRootEditorData, FName InCategoryName, FName InSubcategoryName, FText InDisplayName, FText InToolTip);

private:
	bool bSettingsGroupEnabled;
};
