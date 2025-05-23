#pragma once



class FPanelDesignerBlueprintEditor;

/*
*  Static helper class for registering [Designer] & [Graph] toolbar buttons.
*/
class FPanelDesignerToolbar
{
public:

	static void RegisterToolbar(UBlueprint* InBlueprint, TSharedPtr<FPanelDesignerBlueprintEditor> InEditor);
};