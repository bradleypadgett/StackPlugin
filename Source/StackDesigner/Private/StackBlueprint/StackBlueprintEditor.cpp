#include "StackBlueprintEditor.h"
#include "Graph/StackBlueprintGraph.h"
#include "StackBlueprintExtension.h"
#include "StackBlueprintToolbar.h"
#include "StackBlueprintTests.h"
#include "StackBlueprintMode.h"
#include "BlueprintEditor.h"



// Helper function for initializing application mode properly
static FText GetLocalizedStackBlueprintMode(const FName InMode)
{
	return NSLOCTEXT("StackBlueprint", "StackBlueprint", "Panel Designer");
}

void FStackBlueprintEditor::RegisterApplicationModes(const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode, bool bNewlyCreated)
{
	StackBlueprintToolbar = FStackBlueprintToolbar::RegisterToolbar(GetBlueprintObj(), SharedThis(this));
	AddToolbarExtender(StackBlueprintToolbar);

	FBlueprintEditor::RegisterApplicationModes(InBlueprints, bShouldOpenInDefaultsMode, bNewlyCreated);
	
	AddApplicationMode("StackBlueprint", MakeShareable(new FStackBlueprintMode(SharedThis(this), "StackBlueprint", GetLocalizedStackBlueprintMode, false)));

	Extension->EnsureStackBlueprintGraph();
}

void FStackBlueprintEditor::InitalizeExtenders()
{
	FBlueprintEditor::InitalizeExtenders();

	for (UBlueprintExtension* FindExtension : GetBlueprintObj()->GetExtensions())
	{
		if (UStackBlueprintExtension* Found = Cast<UStackBlueprintExtension>(FindExtension))
		{
			Extension = Found;

			UE_LOG(LogTemp, Warning, TEXT("Existing extension was found!"));
			UE_LOG(LogTemp, Warning, TEXT("Extension Outer: %s"), *GetNameSafe(Extension->GetOuter()));
			UE_LOG(LogTemp, Warning, TEXT("Extension Flags: %s%s"), Extension->HasAnyFlags(RF_Transient) ? TEXT("[Transient] ") : TEXT(""), Extension->HasAnyFlags(RF_Standalone) ? TEXT("[Standalone] ") : TEXT(""));
			UE_LOG(LogTemp, Warning, TEXT("Extension is valid: %s, Class: %s"), *GetNameSafe(Extension), Extension ? *Extension->GetClass()->GetName() : TEXT("NULL"));

			return;
		}
	}

	Extension = NewObject<UStackBlueprintExtension>(GetBlueprintObj(), NAME_None, RF_Transactional);

	UE_LOG(LogTemp, Warning, TEXT("New extension was created!"));
	UE_LOG(LogTemp, Warning, TEXT("Extension Outer: %s"), *GetNameSafe(Extension->GetOuter()));
	UE_LOG(LogTemp, Warning, TEXT("Extension Flags: %s%s"), Extension->HasAnyFlags(RF_Transient) ? TEXT("[Transient] ") : TEXT(""), Extension->HasAnyFlags(RF_Standalone) ? TEXT("[Standalone] ") : TEXT(""));
	UE_LOG(LogTemp, Warning, TEXT("Extension is valid: %s, Class: %s"), *GetNameSafe(Extension), Extension ? *Extension->GetClass()->GetName() : TEXT("NULL"));

	GetBlueprintObj()->AddExtension(Extension);
}

void FStackBlueprintEditor::HandleCurrentMode(FName InMode)
{
	if (InMode == "StackBlueprint") bDetailsOpeninDefaultMode = GetTabManager()->FindExistingLiveTab(FName("Inspector")).IsValid();

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

UStackBlueprintGraph* FStackBlueprintEditor::GetStackBlueprintGraph() { return Extension->GetStackBlueprintGraph(); }

void FStackBlueprintEditor::OnClose()
{
	if (Extension) { Extension = nullptr; }
	if (PlaceholderWidget.IsValid()) { PlaceholderWidget.Reset(); }

	if (StackBlueprintToolbar.IsValid()) 
	{
		RemoveToolbarExtender(StackBlueprintToolbar);
		StackBlueprintToolbar.Reset();
		RegenerateMenusAndToolbars();
	}

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

TSharedRef<SStackBlueprintPlaceholderWidget> FStackBlueprintEditor::GetPlaceholderWidget()
{
	if (!PlaceholderWidget) PlaceholderWidget = SNew(SStackBlueprintPlaceholderWidget);

	return PlaceholderWidget.ToSharedRef();
}