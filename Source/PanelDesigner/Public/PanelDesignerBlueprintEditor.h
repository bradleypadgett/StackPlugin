#pragma once
#include "BlueprintEditor.h"
#include "BlueprintEditorModes.h"



class FBlueprintEditor;
class UPanelDesignerBlueprintExtension;
class FPanelDesignerMode;

class FPanelDesignerBlueprintEditor : public FBlueprintEditor
{

public:

	FPanelDesignerBlueprintEditor();
	~FPanelDesignerBlueprintEditor();

	static TWeakPtr<FPanelDesignerBlueprintEditor> Debug_WeakRef;

	void RegisterApplicationModes(const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode, bool bNewlyCreated = false) override;

	// this function is misspelled ?? backwards compatibility I suppose hell ya lmfao 💀
	void InitalizeExtenders() override;

	UPanelDesignerBlueprintExtension* GetExtension() { return Extension; }

	void PostInitAssetEditor() override;

	void HandleCurrentMode(FName InMode);

	void OnClose() override;

	bool bDetailsOpeninDefaultMode;

	//virtual bool IsWorldCentricAssetEditor() const { UE_LOG(LogTemp, Warning, TEXT("📎 IsWorldCentricAssetEditor() called — returning: %s"), bIsWorldCentricAssetEditor ? TEXT("true") : TEXT("false")); return bIsWorldCentricAssetEditor; };

	//bool bIsWorldCentricAssetEditor = false;

private:


	UPanelDesignerBlueprintExtension* Extension;

	TSharedPtr<FPanelDesignerMode> DesignerMode;

};