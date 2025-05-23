#pragma once
#include "BlueprintEditorModes.h"



class UPanelDesignerBlueprintExtension;


/*
*  Initializes and handles application modes inside blueprint. 
*/
class FPanelDesignerBlueprintEditor : public FBlueprintEditor
{
public:

	void RegisterApplicationModes(const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode, bool bNewlyCreated = false) override;

	void InitalizeExtenders() override;
	UPanelDesignerBlueprintExtension* GetExtension() { return Extension; }

	void HandleCurrentMode(FName InMode);

	void OnClose() override;

	bool bDetailsOpeninDefaultMode;

private:

	UPanelDesignerBlueprintExtension* Extension;
};