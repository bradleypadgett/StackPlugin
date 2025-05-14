#include "ReplicatedBlueprintEditorMode.h"
#include "BlueprintEditorTabs.h"
#include "BlueprintEditor.h"

static FText GetLocalizedReplicatedBlueprintEditorMode(FName InMode)
{
	return FText::FromString("BlueprintMode");
}

FReplicatedBlueprintEditorMode::FReplicatedBlueprintEditorMode(TSharedPtr<FBlueprintEditor> InEditor) : FApplicationMode("BlueprintMode", GetLocalizedReplicatedBlueprintEditorMode)
{
	// Epic-style default layout
	TabLayout = FTabManager::NewLayout("PanelDesigner_DefaultLayout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				// Main 3-panel horizontal section
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->Split(
					FTabManager::NewStack()
					->AddTab(FBlueprintEditorTabs::MyBlueprintID, ETabState::OpenedTab)
					->SetSizeCoefficient(0.2f)
				)
				->Split(
					FTabManager::NewStack()
					->AddTab(FBlueprintEditorTabs::GraphEditorID, ETabState::OpenedTab)
					->SetSizeCoefficient(0.6f)
				)
				->Split(
					FTabManager::NewStack()
					->AddTab(FBlueprintEditorTabs::DetailsID, ETabState::OpenedTab)
					->AddTab(FBlueprintEditorTabs::PaletteID, ETabState::ClosedTab)
					->SetSizeCoefficient(0.2f)
				)
			)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(FBlueprintEditorTabs::FindResultsID, ETabState::ClosedTab)
				->AddTab(FBlueprintEditorTabs::CompilerResultsID, ETabState::ClosedTab)
				->AddTab(FBlueprintEditorTabs::BookmarksID, ETabState::ClosedTab)
				->SetHideTabWell(false)
				->SetSizeCoefficient(0.15f)
			)
		);
}
