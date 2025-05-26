#include "PanelDesignerEditor.h"
#include "Framework/Docking/LayoutService.h"
#include "PanelDesignerExtension.h"
#include "Graph/PanelDesignerGraph.h"
#include "PanelDesignerToolbar.h"
#include "PanelDesignerMode.h"
#include "BlueprintEditor.h"
#include "PanelDesignerTests.h"
#include "Widgets/SCompoundWidget.h"



// Helper function for initializing application mode properly
static FText GetLocalizedPanelDesignerMode(const FName InMode)
{
	return NSLOCTEXT("PanelDesigner", "PanelDesigner", "Panel Designer");
}

void FPanelDesignerEditor::RegisterApplicationModes(const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode, bool bNewlyCreated)
{
	PanelDesignerToolbar = FPanelDesignerToolbar::RegisterToolbar(GetBlueprintObj(), SharedThis(this));
	AddToolbarExtender(PanelDesignerToolbar);

	FBlueprintEditor::RegisterApplicationModes(InBlueprints, bShouldOpenInDefaultsMode, bNewlyCreated);
	
	AddApplicationMode("PanelDesigner", MakeShareable(new FPanelDesignerMode(SharedThis(this), "PanelDesigner", GetLocalizedPanelDesignerMode, false)));


	Extension->EnsurePanelDesignerGraph();
}

void FPanelDesignerEditor::InitalizeExtenders()
{
	FBlueprintEditor::InitalizeExtenders();

	for (UBlueprintExtension* FindExtension : GetBlueprintObj()->GetExtensions())
	{
		if (UPanelDesignerExtension* Found = Cast<UPanelDesignerExtension>(FindExtension))
		{
			Extension = Found;

			UE_LOG(LogTemp, Warning, TEXT("Existing extension was found!"));

			UE_LOG(LogTemp, Warning, TEXT("Extension Outer: %s"), *GetNameSafe(Extension->GetOuter()));
			UE_LOG(LogTemp, Warning, TEXT("Extension Flags: %s%s"),
				Extension->HasAnyFlags(RF_Transient) ? TEXT("[Transient] ") : TEXT(""),
				Extension->HasAnyFlags(RF_Standalone) ? TEXT("[Standalone] ") : TEXT(""));

			UE_LOG(LogTemp, Warning, TEXT("Extension is valid: %s, Class: %s"),
				*GetNameSafe(Extension),
				Extension ? *Extension->GetClass()->GetName() : TEXT("NULL"));

			return;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("New extension was created!"));
	Extension = NewObject<UPanelDesignerExtension>(GetBlueprintObj(), NAME_None, RF_Transactional);

	UE_LOG(LogTemp, Warning, TEXT("Extension Outer: %s"), *GetNameSafe(Extension->GetOuter()));
	UE_LOG(LogTemp, Warning, TEXT("Extension Flags: %s%s"),
		Extension->HasAnyFlags(RF_Transient) ? TEXT("[Transient] ") : TEXT(""),
		Extension->HasAnyFlags(RF_Standalone) ? TEXT("[Standalone] ") : TEXT(""));

	UE_LOG(LogTemp, Warning, TEXT("Extension is valid: %s, Class: %s"),
		*GetNameSafe(Extension),
		Extension ? *Extension->GetClass()->GetName() : TEXT("NULL"));


	GetBlueprintObj()->AddExtension(Extension);
}

void FPanelDesignerEditor::HandleCurrentMode(FName InMode)
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

void FPanelDesignerEditor::AttachPanelDesignerGraph()
{
	Extension->AttachPanelDesignerGraph(GetBlueprintObj());
}

UPanelDesignerGraph* FPanelDesignerEditor::GetPanelDesignerGraph()
{
	return Extension->GetPanelDesignerGraph();
}

void FPanelDesignerEditor::OnClose()
{
	//UBlueprint* EditingBP = GetBlueprintObj();
	//if (Extension && GetPanelDesignerGraph()) { CloseDocumentTab(GetPanelDesignerGraph()); }

	//if (GetTabManager().IsValid()) { GetTabManager()->CloseAllAreas(); }

	if (Extension) { Extension = nullptr; }

	if (PlaceholderWidget.IsValid()) { PlaceholderWidget.Reset(); }

	if (PanelDesignerToolbar.IsValid()) 
	{
		UE_LOG(LogTemp, Warning, TEXT("removing toolbar !"));
		RemoveToolbarExtender(PanelDesignerToolbar);
		PanelDesignerToolbar.Reset();
		RegenerateMenusAndToolbars();
	}

	//if (DesignerMode) { DesignerMode->ClearTabFactories(); DesignerMode = nullptr; }	

	UE_LOG(LogTemp, Warning, TEXT("i am closing rawr"));

	//CloseDocumentTab(GetBlueprintObj());
	//DocumentManager->ClearDocumentFactories();

	//RemoveEditingObject(GetBlueprintObj());
	for (UBlueprintExtension* inExtension : GetBlueprintObj()->GetExtensions())
	{
		if (!inExtension) continue;

		UE_LOG(LogTemp, Warning, TEXT("Extension: %s (Class: %s)"),
			*inExtension->GetName(),
			*inExtension->GetClass()->GetName());
	}


	if (GetBlueprintObj()) { GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->NotifyAssetClosed(GetBlueprintObj(), this); }
	
	FBlueprintEditor::OnClose();

}


TSharedRef<SPanelDesignerPlaceholderWidget> FPanelDesignerEditor::GetPlaceholderWidget()
{
	if (!PlaceholderWidget) PlaceholderWidget = SNew(SPanelDesignerPlaceholderWidget);

	return PlaceholderWidget.ToSharedRef();
}
