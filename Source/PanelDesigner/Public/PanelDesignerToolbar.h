#pragma once



class FPanelDesignerBlueprintEditor;

class FPanelDesignerToolbar
{
public:

	static void RegisterToolbar(UBlueprint* InBlueprint, TSharedPtr<FPanelDesignerBlueprintEditor> InEditor);

};
