#pragma once
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "BlueprintEditorModes.h"



class FPanelDesignerBlueprintEditor;

/*
*  Custom application mode for designing panels. It extends the native blueprint application mode for access to native tabs
*/
class FPanelDesignerMode : public FBlueprintEditorUnifiedMode
{
public:

	FPanelDesignerMode(TSharedPtr<class FPanelDesignerBlueprintEditor> InBlueprintEditor, FName InModeName, FText(*GetLocalizedMode)(const FName), const bool bRegisterViewport = true);
	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;

	void PostActivateMode() override;
	void PreDeactivateMode() override;

	TSharedPtr<FTabManager::FLayout> GetTabLayout() const { return TabLayout; }
	
private:

	TWeakPtr<FPanelDesignerBlueprintEditor> WeakEditor;
};