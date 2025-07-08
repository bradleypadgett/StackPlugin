#pragma once
#include "StackGroup.h"
#include "Definition/StackCommonTypes.h"
#include "ViewModels/Editor/StackModuleViewModel.h"
#include "StackModuleGroup.generated.h"



UCLASS()
class UStackModuleGroup : public UStackGroup
{
	GENERATED_BODY()
public:
	virtual void Initialize(
		FStackEntryContext InEntryContext,
		FText InDisplayName,
		FText InToolTip,
		TSharedRef<FStackModuleViewModel> InModuleViewModel,
		EStackModuleUsage InModuleUsage,
		FGuid InModuleUsageId);
	
	FName GetUsageKey() const;

private:
	TSharedPtr<FStackModuleViewModel> ModuleViewModel;
	EStackModuleUsage Usage;
	FGuid UsageId;
};