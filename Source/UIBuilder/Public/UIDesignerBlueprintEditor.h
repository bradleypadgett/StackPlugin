#pragma once
#include "BlueprintEditor.h"
#include "BlueprintEditorModes.h"



class FBlueprintEditor;
class UUIBuilderBlueprintExtension;
class FUIDesignerMode;

class FUIDesignerBlueprintEditor : public FBlueprintEditor
{

public:

	FUIDesignerBlueprintEditor();
	~FUIDesignerBlueprintEditor();

	static TWeakPtr<FUIDesignerBlueprintEditor> Debug_WeakRef;

	void RegisterApplicationModes(const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode, bool bNewlyCreated = false) override;

	// this function is misspelled ?? backwards compatibility I suppose hell ya lmfao 💀
	void InitalizeExtenders() override;

	UUIBuilderBlueprintExtension* GetExtension() { return Extension; }

	void PostInitAssetEditor() override;

	void HandleCurrentMode(FName InMode);

	void OnClose() override;

	bool bDetailsOpeninDefaultMode;

	//virtual bool IsWorldCentricAssetEditor() const { UE_LOG(LogTemp, Warning, TEXT("📎 IsWorldCentricAssetEditor() called — returning: %s"), bIsWorldCentricAssetEditor ? TEXT("true") : TEXT("false")); return bIsWorldCentricAssetEditor; };

	//bool bIsWorldCentricAssetEditor = false;

private:


	UUIBuilderBlueprintExtension* Extension;

	TSharedPtr<FUIDesignerMode> DesignerMode;

};