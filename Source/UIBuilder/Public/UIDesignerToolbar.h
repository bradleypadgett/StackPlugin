#pragma once



class FUIDesignerBlueprintEditor;

class FUIDesignerToolbar
{
public:

	static void RegisterToolbar(UBlueprint* InBlueprint, TSharedPtr<FUIDesignerBlueprintEditor> InEditor);

};
