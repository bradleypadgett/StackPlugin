#pragma once
#include "ViewModels/StackItem.h"
#include "Misc/NotifyHook.h"
#include "StackObject.generated.h"



class IPropertyRowGenerator;
class FStructOnScope;

UCLASS()
class STACKFRAMEWORK_API UStackObject : public UStackItemContent, public FNotifyHook
{
	GENERATED_BODY()

public:
	UStackObject();

	void Initialize(
		const FStackEntryContext& InEntryContext,
		UObject* InObject,
		bool bInIsTopLevel,
		bool bInHideTopLevelCategories,
		FString InOwnerEntryEditorDataKey);

	UObject* GetObject() const { return WeakObject.Get(); }
	virtual UObject* GetDisplayedObject() const override { return GetObject(); }

	// FNotifyHook
	virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;
	virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;
	void OnPropertyRowsRefreshed();

protected:
	virtual void RefreshChildrenInternal(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren, TArray<FStackIssue>& NewIssues) override;
	virtual void FinalizeInternal() override;

protected:
	TWeakObjectPtr<UObject> WeakObject;
	bool bIsTopLevel = false;
	bool bHideTopLevelCategories = false;
	TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;
};
