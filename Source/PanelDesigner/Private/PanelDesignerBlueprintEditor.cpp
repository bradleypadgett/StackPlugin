#include "PanelDesignerBlueprintEditor.h"
#include "Framework/Docking/LayoutService.h"
#include "PanelDesignerBlueprintExtension.h"
#include "PanelDesignerToolbar.h"
#include "PanelDesignerMode.h"
#include "BlueprintEditor.h"



// Helper function for initializing application mode properly
static FText GetLocalizedPanelDesignerMode(const FName InMode)
{
	return NSLOCTEXT("PanelDesigner", "PanelDesigner", "Panel Designer");
}

void FPanelDesignerBlueprintEditor::RegisterApplicationModes(const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode, bool bNewlyCreated)
{
	FPanelDesignerToolbar::RegisterToolbar(GetBlueprintObj(), SharedThis(this));
	
	FBlueprintEditor::RegisterApplicationModes(InBlueprints, bShouldOpenInDefaultsMode, bNewlyCreated);

	AddApplicationMode("PanelDesigner", MakeShareable(new FPanelDesignerMode(SharedThis(this), "PanelDesigner", GetLocalizedPanelDesignerMode, false)));
}

void FPanelDesignerBlueprintEditor::InitalizeExtenders()
{
	FBlueprintEditor::InitalizeExtenders();

	Extension = NewObject<UPanelDesignerBlueprintExtension>(GetBlueprintObj());
	GetBlueprintObj()->AddExtension(Extension);
}

void FPanelDesignerBlueprintEditor::HandleCurrentMode(FName InMode)
{
	if (InMode == "PanelDesigner") bDetailsOpeninDefaultMode = GetTabManager()->FindExistingLiveTab(FName("Inspector")).IsValid();

	SetCurrentMode(InMode);
	
	// Prevents swaps from [Designer] -> [Graph] to auto-select 'Class Defaults' (which forces the details panel open)
	// Edge case to better match blueprints' default layout behavior 
	if (InMode == "GraphName" && bDetailsOpeninDefaultMode == false)
	{
		if (TSharedPtr<SDockTab> DetailsTab = GetTabManager()->FindExistingLiveTab(FName("Inspector")))
		{
			DetailsTab->RequestCloseTab();
			GetInspector()->ShowDetailsForSingleObject(nullptr);
		}
	}
}

void FPanelDesignerBlueprintEditor::OnClose()
{
	UBlueprint* EditingBP = GetBlueprintObj();

	if (EditingBP)
	{
		GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->NotifyAssetClosed(EditingBP, this);

		if (Extension) {
			EditingBP->RemoveExtension(Extension); 
			Extension = nullptr;
		}
	}
	FBlueprintEditor::OnClose();
}