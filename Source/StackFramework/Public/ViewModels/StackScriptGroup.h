#pragma once
#include "StackGroup.h"
#include "Definition/StackCommonTypes.h"
#include "ViewModels/Editor/StackScriptViewModel.h"
#include "StackScriptGroup.generated.h"



UCLASS()
class UStackScriptGroup : public UStackGroup
{
	GENERATED_BODY()
public:
	virtual void Initialize(
		FStackEntryContext InEntryContext,
		FText InDisplayName,
		FText InToolTip,
		TSharedRef<FStackScriptViewModel> InScriptViewModel,
		EScriptCompileTarget InScriptCompileTarget,
		FGuid InGroupID);

private:
	TSharedPtr<FStackScriptViewModel> ScriptViewModel;

};