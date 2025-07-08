#include "ViewModels/StackModuleGroup.h"



void UStackModuleGroup::Initialize(
	FStackEntryContext InEntryContext,
	FText InDisplayName,
	FText InToolTip,
	TSharedRef<FStackModuleViewModel> InModuleViewModel,
	EStackModuleUsage InModuleUsage,
	FGuid InModuleUsageId)
{

}

FName UStackModuleGroup::GetUsageKey() const
{
	return FName(*UsageId.ToString());
}