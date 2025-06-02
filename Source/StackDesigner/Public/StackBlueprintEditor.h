#pragma once
#include "BlueprintEditorModes.h"
#include "StackBlueprintTests.h"



class UStackBlueprintExtension;
class UStackBlueprintGraph;
class FStackBlueprintMode;

/*
*  Initializes and handles application modes inside blueprint. 
*/
class FStackBlueprintEditor : public FBlueprintEditor
{
public:

	void RegisterApplicationModes(const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode, bool bNewlyCreated = false) override;

	void HandleCurrentMode(FName InMode);

	void OnClose() override;

	void InitalizeExtenders() override;
	UStackBlueprintExtension* GetExtension() { return Extension; }

	void AttachStackBlueprintGraph();

	UStackBlueprintGraph* GetStackBlueprintGraph();

	bool bDetailsOpeninDefaultMode;

	//Widgets
	TSharedPtr<SStackBlueprintPlaceholderWidget> PlaceholderWidget;
	TSharedRef<SStackBlueprintPlaceholderWidget> GetPlaceholderWidget();

private:

	TSharedPtr<FExtender> StackBlueprintToolbar;

	UStackBlueprintExtension* Extension;

};