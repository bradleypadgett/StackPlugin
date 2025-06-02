#include "StackBlueprintMode.h"
#include "StackBlueprintTabFactories.h"
#include "BlueprintEditorModes.h"
#include "StackBlueprintEditor.h"
#include "StackBlueprintTabs.h"



// Based on the layout of [FBlueprintEditorApplicationMode]
TSharedPtr<FTabManager::FLayout> GetDefaultEditorLayout(TSharedPtr<class FStackBlueprintEditor> InBlueprintEditor)
{
	return FTabManager::NewLayout("StackBlueprint_DefaultLayout_v1")
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
					->AddTab(FStackBlueprintTabs::SelectionID, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.4f)
					->AddTab(FStackBlueprintTabs::VariablesID, ETabState::OpenedTab)
					->AddTab(FStackBlueprintTabs::PaletteID, ETabState::OpenedTab)
					->SetForegroundTab(FStackBlueprintTabs::VariablesID)
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
					->AddTab(FStackBlueprintTabs::DesignerGraphID, ETabState::OpenedTab)
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
					->AddTab(FStackBlueprintTabs::PreviewID, ETabState::OpenedTab)
					//->AddTab(FBlueprintEditorTabs::DetailsID, ETabState::OpenedTab)
					//->AddTab(FBlueprintEditorTabs::PaletteID, ETabState::ClosedTab)
				)
			)
		)
	);
}

// Initializes custom application mode. Extends [FBlueprintEditorApplicationMode] for access to native Blueprint tabs
FStackBlueprintMode::FStackBlueprintMode(TSharedPtr<class FStackBlueprintEditor> InBlueprintEditor, FName InModeName, FText(*GetLocalizedMode)(const FName), const bool bRegisterViewport, const bool bRegisterDefaultsTab)
	: FBlueprintEditorApplicationMode(InBlueprintEditor, InModeName, GetLocalizedMode, bRegisterViewport, bRegisterDefaultsTab)
{
	BlueprintEditor = InBlueprintEditor;

	StackBlueprintTabFactories.RegisterFactory(MakeShareable(new FDesignerGraphSummoner(InBlueprintEditor)));
	StackBlueprintTabFactories.RegisterFactory(MakeShareable(new FSelectionSummoner(InBlueprintEditor)));
	StackBlueprintTabFactories.RegisterFactory(MakeShareable(new FVariableSummoner(InBlueprintEditor)));
	StackBlueprintTabFactories.RegisterFactory(MakeShareable(new FPaletteSummoner(InBlueprintEditor)));
	StackBlueprintTabFactories.RegisterFactory(MakeShareable(new FPreviewSummoner(InBlueprintEditor)));

	BlueprintEditorTabFactories.Clear();
	CoreTabFactories.Clear();
	BlueprintEditorOnlyTabFactories.Clear();

	TabLayout = GetDefaultEditorLayout(InBlueprintEditor);
}

// Calls helper class to initialize tabs
void FStackBlueprintMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	TSharedPtr<FStackBlueprintEditor> Editor = StaticCastSharedPtr<FStackBlueprintEditor>(BlueprintEditor.Pin());

	Editor->PushTabFactories(StackBlueprintTabFactories);

	FBlueprintEditorApplicationMode::RegisterTabFactories(InTabManager);
}

// Automatically invoked when application mode is opened. Attempts to re-load layout & regenerates graph tab if none are open.
void FStackBlueprintMode::PostActivateMode()
{
	FBlueprintEditorApplicationMode::PostActivateMode();

	TSharedPtr<FStackBlueprintEditor> Editor = StaticCastSharedPtr<FStackBlueprintEditor>(MyBlueprintEditor.Pin());
	TSharedPtr<FTabManager> TabManager = Editor->GetTabManager();

	if (!TabManager->FindExistingLiveTab(FStackBlueprintTabs::SelectionID).IsValid() &&
		!TabManager->FindExistingLiveTab(FStackBlueprintTabs::VariablesID).IsValid() &&
		!TabManager->FindExistingLiveTab(FStackBlueprintTabs::PreviewID).IsValid())
	{
		TabManager->TryInvokeTab(FStackBlueprintTabs::DesignerGraphID);
	}
}