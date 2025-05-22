#pragma once
#include "BlueprintEditor.h"
#include "BlueprintEditorModes.h"



class FBlueprintEditor;
class UUIBuilderBlueprintExtension;
class FUIDesignerMode;

class FUIDesignerBlueprintEditor : public FBlueprintEditor
{

public:

	void RegisterApplicationModes(const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode, bool bNewlyCreated = false) override;

	// this function is misspelled ?? backwards compatibility I suppose hell ya lmfao 💀
	void InitalizeExtenders() override;

	UUIBuilderBlueprintExtension* GetExtension() { return Extension; }

	void PostInitAssetEditor() override;

	void HandleCurrentMode(FName InMode);

	void OnClose() override;

	bool bDetailsOpeninDefaultMode;


private:

	UUIBuilderBlueprintExtension* Extension;

	TSharedPtr<FUIDesignerMode> DesignerMode;

};