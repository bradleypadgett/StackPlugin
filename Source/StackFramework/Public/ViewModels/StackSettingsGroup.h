#pragma once
#include "Utilities/StackGroupAddUtilities.h"
#include "ViewModels/StackEntry.h"
#include "ViewModels/StackItem.h"
#include "ViewModels/StackGroup.h"
#include "StackSettingsGroup.generated.h"



class UStackGroup;
class UStackScriptGroup;

UCLASS()
class UStackSettingsGroup : public UStackGroup
{
	GENERATED_BODY()
public:
	UStackSettingsGroup();

	virtual void Initialize(FStackEntryContext InContext);

	virtual bool GetCanExpandInNode() const override { return false; }
	virtual bool GetShouldShowInStack() const override { return false; }

protected:
	virtual void RefreshChildrenInternal(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren, TArray<FStackIssue>& NewIssues) override;

	void OnGroupAdded(UStackScriptGroup* NewGroup);

private:
	UPROPERTY()
	TObjectPtr<UStackSettingsItem> SettingsItem;

	TSharedPtr<IStackGroupAddUtilities> AddUtilities;

	// TO-DO ~ Add to UStack later
	UPROPERTY()
	TArray<TObjectPtr<UStackScriptGroup>> AddedGroups;
};

UCLASS()
class STACKFRAMEWORK_API UStackSettingsItem : public UStackItem
{
	GENERATED_BODY()

public:
	void Initialize(FStackEntryContext InContext);

	virtual FText GetDisplayName() const override { return NSLOCTEXT("Stack", "SettingsItem", "Settings"); }
	virtual FText GetTooltipText() const override { return NSLOCTEXT("Stack", "SettingsItemTooltip", "Settings for this section"); }

	virtual bool CanResetItem() const override { return false; }
	virtual bool GetShouldShowInStack() const override { return false; }

protected:
	virtual void FinalizeInternal() override { return; };
	virtual void RefreshChildrenInternal(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren, TArray<FStackIssue>& NewIssues) override;

private:
	//UPROPERTY()
	//TObjectPtr<UStackObject> SettingsObject;
};

class FStackSettingsAddUtilities : public FStackGroupAddUtilities
{
public:
	DECLARE_DELEGATE_OneParam(FOnItemAdded, UStackScriptGroup* /* NewGroup */);

	FStackSettingsAddUtilities(UStackSettingsGroup* InOwningGroup, FOnItemAdded InOnItemAdded)
		: FStackGroupAddUtilities(FText::FromString("Settings Entry"), EAddMode::AddDirectly, false, true)
		, OwningGroup(InOwningGroup)
		, OnItemAdded(InOnItemAdded)
	{
	}

	virtual void GenerateAddActions(TArray<TSharedRef<FStackAddAction>>& OutActions) const override;
	virtual void ExecuteAddAction(TSharedRef<FStackAddAction> Action, int32 TargetIndex) override;
	virtual void AddItemDirectly() override;

private:
	TWeakObjectPtr<UStackSettingsGroup> OwningGroup;
	FOnItemAdded OnItemAdded;
};