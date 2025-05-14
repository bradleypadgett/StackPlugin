#include "UIDesignerBlueprintEditor.h"
#include "ReplicatedBlueprintEditorMode.h"
#include "UIDesignerMode.h"
#include "BlueprintEditor.h"



void FUIDesignerBlueprintEditor::InitUIDesignerEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UBlueprint* Blueprint)
{
	TArray<UBlueprint*> Blueprints = { Blueprint };
	InitBlueprintEditor(Mode, InitToolkitHost, Blueprints, true);

	AddApplicationMode("BlueprintMode", MakeShareable(new FReplicatedBlueprintEditorMode(StaticCastSharedRef<FBlueprintEditor>(AsShared()))));
	AddApplicationMode("PanelDesignerMode", MakeShareable(new FUIDesignerMode(StaticCastSharedRef<FBlueprintEditor>(AsShared()))));

	SetCurrentMode("BlueprintMode");
}
