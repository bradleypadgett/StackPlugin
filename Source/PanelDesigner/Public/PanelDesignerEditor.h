#pragma once
#include "BlueprintEditorModes.h"
#include "PanelDesignerTests.h"
#include "Toolkits/AssetEditorToolkit.h"



class UPanelDesignerExtension;
class UPanelDesignerGraph;
class FPanelDesignerMode;

/*
*  Initializes and handles application modes inside blueprint. 
*/
class FPanelDesignerEditor : public FBlueprintEditor
{
public:

	void RegisterApplicationModes(const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode, bool bNewlyCreated = false) override;

	void HandleCurrentMode(FName InMode);

	void OnClose() override;

	void InitalizeExtenders() override;
	UPanelDesignerExtension* GetExtension() { return Extension; }

	void AttachPanelDesignerGraph();

	UPanelDesignerGraph* GetPanelDesignerGraph();

	bool bDetailsOpeninDefaultMode;

	//Widgets
	TSharedPtr<SPanelDesignerPlaceholderWidget> PlaceholderWidget;
	TSharedRef<SPanelDesignerPlaceholderWidget> GetPlaceholderWidget();

private:

	TSharedPtr<FExtender> PanelDesignerToolbar;

	UPanelDesignerExtension* Extension;

};