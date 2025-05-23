#include "PanelDesignerBlueprintEditor.h"
#include "Framework/Docking/LayoutService.h"
#include "PanelDesignerBlueprintExtension.h"
#include "PanelDesignerToolbar.h"
#include "BlueprintEditor.h"
#include "PanelDesignerMode.h"
#include "Templates/SharedPointerInternals.h"
#include "Toolkits/IToolkit.h"
#include "Toolkits/ToolkitManager.h"



FPanelDesignerBlueprintEditor::FPanelDesignerBlueprintEditor()
{
	UE_LOG(LogTemp, Warning, TEXT("🛠️ FPanelDesignerBlueprintEditor constructor called"));
}

FPanelDesignerBlueprintEditor::~FPanelDesignerBlueprintEditor()
{
	UE_LOG(LogTemp, Warning, TEXT("🧹 FPanelDesignerBlueprintEditor destroyed"));
}



static FText GetLocalizedPanelDesignerMode(const FName InMode)
{
	return NSLOCTEXT("PanelDesigner", "PanelDesigner", "Panel Designer");
}

void FPanelDesignerBlueprintEditor::RegisterApplicationModes(const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode, bool bNewlyCreated)
{
	// RegisterMenus() isn't overrideable- so I'm putting toolbar registration here to save me a RegenerateMenusAndToolbars() call!
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

void FPanelDesignerBlueprintEditor::PostInitAssetEditor()
{
	FBlueprintEditor::PostInitAssetEditor();
}

void FPanelDesignerBlueprintEditor::HandleCurrentMode(FName InMode)
{
	if (InMode == "PanelDesigner") bDetailsOpeninDefaultMode = GetTabManager()->FindExistingLiveTab(FName("Inspector")).IsValid();

	SetCurrentMode(InMode);
	
	// This little goofy block prevents swaps from [Designer] -> [Graph] to auto-select 'Class Defaults' (which forces the details panel open)
	// Just a subtle change so I can better match blueprints' default layout behavior 
	if (InMode == "GraphName" && bDetailsOpeninDefaultMode == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("🚀 bDetailsOpeninDefaultMode is false!"));
		if (TSharedPtr<SDockTab> DetailsTab = GetTabManager()->FindExistingLiveTab(FName("Inspector")))
		{
			UE_LOG(LogTemp, Warning, TEXT("🚀 Attempting to close document tab"));
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
