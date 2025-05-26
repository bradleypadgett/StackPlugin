#pragma once
#include "WorkflowOrientedApp/WorkflowTabManager.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "BlueprintEditorModes.h"



class FPanelDesignerEditor;

/*
*  Custom application mode for designing panels. It extends the native blueprint application mode for access to native tabs
*/
class FPanelDesignerMode : public FBlueprintEditorApplicationMode
{
public:
	FPanelDesignerMode(TSharedPtr<class FPanelDesignerEditor> InBlueprintEditor, FName InModeName, FText(*GetLocalizedMode)(const FName), const bool bRegisterViewport = false, const bool bRegisterDefaultsTab = false);
	
	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;
	void PostActivateMode() override;
	void PreDeactivateMode() override;

	void ClearTabFactories();
	
	TSharedPtr<FTabManager::FLayout> GetTabLayout() const { return TabLayout; }
	
	
protected:
	TWeakPtr<FPanelDesignerEditor> BlueprintEditor;

	FWorkflowAllowedTabSet PanelDesignerTabFactories;

};