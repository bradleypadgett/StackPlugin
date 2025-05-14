#pragma once
#include "WorkflowOrientedApp/ApplicationMode.h"



class FBlueprintEditor;

class FUIDesignerMode : public FApplicationMode
{
public:

	FUIDesignerMode(TSharedPtr<FBlueprintEditor> InBlueprintEditor);

	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;

	TSharedPtr<FTabManager::FLayout> TabLayout;

private:
	TWeakPtr<FBlueprintEditor> WeakBlueprintEditor;
};
