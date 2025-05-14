#pragma once
#include "BlueprintEditor.h"



class FUIDesignerBlueprintEditor : public FBlueprintEditor
{

public:

	void InitUIDesignerEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UBlueprint* Blueprint);

};