#pragma once
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "BlueprintEditorModes.h"



class FUIDesignerBlueprintEditor;

class FUIDesignerMode : public FBlueprintEditorUnifiedMode
{
public:

	FUIDesignerMode(TSharedPtr<class FUIDesignerBlueprintEditor> InBlueprintEditor, FName InModeName, FText(*GetLocalizedMode)(const FName), const bool bRegisterViewport = true);

	//FUIDesignerMode(TSharedPtr<FUIDesignerBlueprintEditor> InEditor);

	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;

	void PostActivateMode() override;

	void PreDeactivateMode() override;

	//TSharedPtr<FTabManager::FLayout> TabLayout;

	TSharedPtr<FTabManager::FLayout> GetTabLayout() const { return TabLayout; }
	
private:

	TWeakPtr<FUIDesignerBlueprintEditor> WeakEditor;

};
