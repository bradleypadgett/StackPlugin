#pragma once
#include "WorkflowOrientedApp/ApplicationMode.h"



class FUIDesignerBlueprintEditor;
class FUIDesignerBlueprintEditor;

class FUIDesignerMode : public FApplicationMode
{
public:

	FUIDesignerMode(TSharedPtr<FUIDesignerBlueprintEditor> InEditor);

	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;

	void PostActivateMode() override;

	void PreDeactivateMode() override;

	//TSharedPtr<FTabManager::FLayout> TabLayout;

	TSharedPtr<FTabManager::FLayout> GetTabLayout() const { return TabLayout; }
	
private:

	TWeakPtr<FUIDesignerBlueprintEditor> WeakEditor;

};
