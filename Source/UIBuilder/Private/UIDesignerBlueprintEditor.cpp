#include "UIDesignerBlueprintEditor.h"
#include "Framework/Docking/LayoutService.h"
#include "UIBuilderBlueprintExtension.h"
#include "UIDesignerToolbar.h"
#include "BlueprintEditor.h"
#include "UIDesignerMode.h"
#include "Templates/SharedPointerInternals.h"
#include "Toolkits/IToolkit.h"
#include "Toolkits/ToolkitManager.h"



FUIDesignerBlueprintEditor::FUIDesignerBlueprintEditor()
{
	UE_LOG(LogTemp, Warning, TEXT("🛠️ FUIDesignerBlueprintEditor constructor called"));
}

FUIDesignerBlueprintEditor::~FUIDesignerBlueprintEditor()
{
	UE_LOG(LogTemp, Warning, TEXT("🧹 FUIDesignerBlueprintEditor destroyed"));
}



static FText GetLocalizedPanelDesignerMode(const FName InMode)
{
	return NSLOCTEXT("PanelDesigner", "PanelDesigner", "Panel Designer");
}

void FUIDesignerBlueprintEditor::RegisterApplicationModes(const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode, bool bNewlyCreated)
{
	// RegisterMenus() isn't overrideable- so I'm putting toolbar registration here to save me a RegenerateMenusAndToolbars() call!
	FUIDesignerToolbar::RegisterToolbar(GetBlueprintObj(), SharedThis(this));

	FBlueprintEditor::RegisterApplicationModes(InBlueprints, bShouldOpenInDefaultsMode, bNewlyCreated);

	AddApplicationMode("PanelDesigner", MakeShareable(new FUIDesignerMode(SharedThis(this), "PanelDesigner", GetLocalizedPanelDesignerMode, false)));

}

void FUIDesignerBlueprintEditor::InitalizeExtenders()
{
	FBlueprintEditor::InitalizeExtenders();

	Extension = NewObject<UUIBuilderBlueprintExtension>(GetBlueprintObj());
	GetBlueprintObj()->AddExtension(Extension);
}

void FUIDesignerBlueprintEditor::PostInitAssetEditor()
{
	FBlueprintEditor::PostInitAssetEditor();
}

void FUIDesignerBlueprintEditor::HandleCurrentMode(FName InMode)
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


void FUIDesignerBlueprintEditor::OnClose()
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
