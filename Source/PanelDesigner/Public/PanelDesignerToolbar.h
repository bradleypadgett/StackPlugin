#pragma once



class FPanelDesignerEditor;

/*
*  Static helper class for registering [Designer] & [Graph] toolbar buttons.
*/
class FPanelDesignerToolbar
{
public:

	static TSharedPtr<FExtender> RegisterToolbar(UBlueprint* InBlueprint, TSharedPtr<FPanelDesignerEditor> InEditor);
};