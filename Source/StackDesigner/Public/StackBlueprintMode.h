#pragma once
#include "WorkflowOrientedApp/WorkflowTabManager.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "BlueprintEditorModes.h"



class FStackBlueprintEditor;

/*
*  Custom application mode for designing panels. It extends the native blueprint application mode for access to native tabs
*/
class FStackBlueprintMode : public FBlueprintEditorApplicationMode
{
public:
	TSharedPtr<FTabManager::FLayout> GetTabLayout() const { return TabLayout; }

	FStackBlueprintMode(TSharedPtr<class FStackBlueprintEditor> InBlueprintEditor, FName InModeName, FText(*GetLocalizedMode)(const FName), const bool bRegisterViewport = false, const bool bRegisterDefaultsTab = false);
	
	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;

	void PostActivateMode() override;
	
protected:
	TWeakPtr<FStackBlueprintEditor> BlueprintEditor;

	FWorkflowAllowedTabSet StackBlueprintTabFactories;

};