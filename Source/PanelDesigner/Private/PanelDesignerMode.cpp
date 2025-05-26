#include "PanelDesignerMode.h"
#include "PanelDesignerEditor.h"
#include "BlueprintEditorModes.h"
#include "BlueprintEditorTabs.h"
#include "BlueprintEditorSharedTabFactories.h"
#include "PanelDesignerTabFactories.h"
#include "Graph/PanelDesignerGraph.h"
#include "PanelDesignerTabs.h"



// Extends the layout of [FBlueprintEditorApplicationMode]
TSharedPtr<FTabManager::FLayout> GetDefaultEditorLayout(TSharedPtr<class FPanelDesignerEditor> InBlueprintEditor)
{
	return FTabManager::NewLayout("PanelDesigner_DefaultLayout_v1")
	->AddArea
	(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
				->SetSizeCoefficient(0.2f)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.6f)
					//->AddTab(FBlueprintEditorTabs::ConstructionScriptEditorID, ETabState::OpenedTab)
					->AddTab(FPanelDesignerTabs::SelectionID, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.4f)
					->AddTab(FPanelDesignerTabs::VariablesID, ETabState::OpenedTab)
					->AddTab(FPanelDesignerTabs::PaletteID, ETabState::OpenedTab)
					->SetForegroundTab(FPanelDesignerTabs::VariablesID)
					//->AddTab(FBlueprintEditorTabs::MyBlueprintID, ETabState::OpenedTab)
				)
			)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
				->SetSizeCoefficient(0.55f)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.80f)
					//->AddTab(FBlueprintEditorTabs::SCSViewportID, ETabState::OpenedTab)
					->AddTab(FPanelDesignerTabs::DesignerGraphID, ETabState::OpenedTab)
					->SetHideTabWell(true)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.20f)
					//->AddTab(FBlueprintEditorTabs::CompilerResultsID, ETabState::ClosedTab)
					//->AddTab(FBlueprintEditorTabs::FindResultsID, ETabState::ClosedTab)
					//->AddTab(FBlueprintEditorTabs::BookmarksID, ETabState::ClosedTab)
				)
			)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
				->SetSizeCoefficient(0.25f)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.55f)
					->AddTab(FPanelDesignerTabs::PreviewID, ETabState::OpenedTab)
					//->AddTab(FBlueprintEditorTabs::DetailsID, ETabState::OpenedTab)
					//->AddTab(FBlueprintEditorTabs::PaletteID, ETabState::ClosedTab)
				)
			)
		)
	);
}

// Initializes custom application mode. Extends [FBlueprintEditorApplicationMode] for access to native Blueprint tabs
FPanelDesignerMode::FPanelDesignerMode(TSharedPtr<class FPanelDesignerEditor> InBlueprintEditor, FName InModeName, FText(*GetLocalizedMode)(const FName), const bool bRegisterViewport, const bool bRegisterDefaultsTab)
	: FBlueprintEditorApplicationMode(InBlueprintEditor, InModeName, GetLocalizedMode, bRegisterViewport, bRegisterDefaultsTab)
{
	BlueprintEditor = InBlueprintEditor;

	PanelDesignerTabFactories.RegisterFactory(MakeShareable(new FDesignerGraphSummoner(InBlueprintEditor)));
	PanelDesignerTabFactories.RegisterFactory(MakeShareable(new FSelectionSummoner(InBlueprintEditor)));
	PanelDesignerTabFactories.RegisterFactory(MakeShareable(new FVariableSummoner(InBlueprintEditor)));
	PanelDesignerTabFactories.RegisterFactory(MakeShareable(new FPaletteSummoner(InBlueprintEditor)));
	PanelDesignerTabFactories.RegisterFactory(MakeShareable(new FPreviewSummoner(InBlueprintEditor)));

	BlueprintEditorTabFactories.Clear();
	CoreTabFactories.Clear();
	BlueprintEditorOnlyTabFactories.Clear();

	TabLayout = GetDefaultEditorLayout(InBlueprintEditor);
}

// Calls helper class to initialize tabs
void FPanelDesignerMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	TSharedPtr<FPanelDesignerEditor> Editor = StaticCastSharedPtr<FPanelDesignerEditor>(BlueprintEditor.Pin());

	Editor->PushTabFactories(PanelDesignerTabFactories);

	FBlueprintEditorApplicationMode::RegisterTabFactories(InTabManager);
}

// Automatically invoked when application mode is opened. Attempts to re-load layout & regenerates graph tab if none are open.
void FPanelDesignerMode::PostActivateMode()
{
	FBlueprintEditorApplicationMode::PostActivateMode();

	TSharedPtr<FPanelDesignerEditor> Editor = StaticCastSharedPtr<FPanelDesignerEditor>(MyBlueprintEditor.Pin());

	TSharedPtr<FTabManager> TabManager = Editor->GetTabManager();

	//Editor->RestoreFromLayout(TabLayout.ToSharedRef());

	if (!TabManager->FindExistingLiveTab(FPanelDesignerTabs::SelectionID).IsValid() &&
		!TabManager->FindExistingLiveTab(FPanelDesignerTabs::VariablesID).IsValid() &&
		!TabManager->FindExistingLiveTab(FPanelDesignerTabs::PreviewID).IsValid())
	{
		TabManager->TryInvokeTab(FPanelDesignerTabs::DesignerGraphID);
	}
}

// Automatically invoked when application mode is closed. Saves layout for syncing between sessions & blueprints
void FPanelDesignerMode::PreDeactivateMode()
{

	//if (TSharedPtr<FPanelDesignerEditor> Editor = StaticCastSharedPtr<FPanelDesignerEditor>(MyBlueprintEditor.Pin());

	//Editor->SaveEditedObjectState();

	FBlueprintEditorApplicationMode::PreDeactivateMode();
}

void FPanelDesignerMode::ClearTabFactories()
{
	PanelDesignerTabFactories.UnregisterFactory(FPanelDesignerTabs::SelectionID);
	PanelDesignerTabFactories.UnregisterFactory(FPanelDesignerTabs::VariablesID);
	PanelDesignerTabFactories.UnregisterFactory(FPanelDesignerTabs::PreviewID);

	PanelDesignerTabFactories.Clear();
}