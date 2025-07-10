#pragma once
#include "ViewModels/StackEntry.h"
#include "Layout/Visibility.h"
#include "UObject/ObjectPtr.h"
#include "StackGroup.generated.h"



class IStackGroupAddUtilities;

// TO-DO ~ Add in footer !
//class UStackGroupFooter;

UCLASS()
class STACKFRAMEWORK_API UStackGroup : public UStackEntry
{
	GENERATED_BODY()

public:
	void Initialize(FStackEntryContext InContext, FText InDisplayName, FText InToolTip, IStackGroupAddUtilities* InAddUtilities);

	virtual FText GetDisplayName() const override;
	//virtual EStackRowStyle GetRowStyle() const override;
	virtual FText GetTooltipText() const override;

	virtual bool GetCanExpandInNode() const override { return true; }
	virtual bool GetIsEnabled() const override { return true; }
	virtual void SetIsEnabled(bool bEnabled) {}
	virtual bool SupportsChangeEnabled() const { return false; }

	virtual bool SupportsSecondaryIcon() const { return false; }
	virtual const FSlateBrush* GetSecondaryIconBrush() const { return nullptr; }

	IStackGroupAddUtilities* GetAddUtilities() const;

protected:
	void SetDisplayName(FText InDisplayName);

	virtual void RefreshStackChildren(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren, TArray<FStackIssue>& NewIssues) override;

	virtual int32 GetChildIndentLevel() const override;

	virtual void ChildStructureChangedInternal() override;

private:
	bool FilterChildrenWithIssues(const UStackEntry& Child) const;

private:
	//UPROPERTY()
	//TObjectPtr<UStackGroupFooter> GroupFooter;

	IStackGroupAddUtilities* AddUtilities = nullptr;

	FText GroupDisplayName;
	FText GroupToolTip;

	mutable TOptional<uint32> RecursiveStackIssuesCount;
	mutable TOptional<EIssueSeverity> HighestIssueSeverity;
};
