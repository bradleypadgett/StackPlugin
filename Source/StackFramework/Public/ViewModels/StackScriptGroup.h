#pragma once
#include "StackGroup.h"
#include "Utilities/StackCommonTypes.h"
#include "ViewModels/Editor/StackScriptManager.h"
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
		TSharedRef<FStackScriptManager> InScriptManager,
		EScriptCompileTarget InScriptCompileTarget,
		FGuid InGroupID);

private:
	TSharedPtr<FStackScriptManager> ScriptManager;

};