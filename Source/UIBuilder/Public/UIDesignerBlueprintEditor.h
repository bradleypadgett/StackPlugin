#pragma once
#include "BlueprintEditor.h"
#include "BlueprintEditorModes.h"



class FBlueprintEditor;
class UUIBuilderBlueprintExtension;

class FUIDesignerBlueprintEditor : public FBlueprintEditor
{

public:

	FUIDesignerBlueprintEditor() = default;

	static void CreateEditor(EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& ToolkitHost, UBlueprint* Blueprint);

	void InitUIDesignerMode(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UBlueprint* Blueprint);

    void PostInitAssetEditor() override;

    static FName GetEditorAppName();

};