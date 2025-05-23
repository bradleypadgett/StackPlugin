#pragma once
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "BlueprintEditorModes.h"



class FPanelDesignerBlueprintEditor;

class FPanelDesignerMode : public FBlueprintEditorUnifiedMode
{
public:

	FPanelDesignerMode(TSharedPtr<class FPanelDesignerBlueprintEditor> InBlueprintEditor, FName InModeName, FText(*GetLocalizedMode)(const FName), const bool bRegisterViewport = true);

	//FPanelDesignerMode(TSharedPtr<FPanelDesignerBlueprintEditor> InEditor);

	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;

	void PostActivateMode() override;

	void PreDeactivateMode() override;

	//TSharedPtr<FTabManager::FLayout> TabLayout;

	TSharedPtr<FTabManager::FLayout> GetTabLayout() const { return TabLayout; }
	
private:

	TWeakPtr<FPanelDesignerBlueprintEditor> WeakEditor;

};
