#pragma once
#include "ViewModels/StackEntry.h"
#include "StackSelection.generated.h"



UCLASS()
class STACKFRAMEWORK_API UStackSelection : public UStackEntry
{
	GENERATED_BODY()

public:
	void Initialize(FStackEntryContext InEntryContext);

	virtual bool GetCanExpand() const override { return false; }
	virtual bool GetShouldShowInStack() const override { return false; }

	void SetSelectedEntries(const TArray<UStackEntry*>& InSelectedEntries);

protected:
	virtual void RefreshChildrenInternal(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren, TArray<FStackIssue>& NewIssues) override;

private:
	TArray<TWeakObjectPtr<UStackEntry>> SelectedEntries;
};
