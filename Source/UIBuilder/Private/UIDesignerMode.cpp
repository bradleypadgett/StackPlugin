#include "UIDesignerMode.h"
#include "UIDesignerTabs.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"
#include "BlueprintEditor.h"



static FText GetLocalizedUIDesignerMode(FName InMode)
{
	return FText::FromString("UI Designer");
}

FUIDesignerMode::FUIDesignerMode(TSharedPtr<FUIDesignerBlueprintEditor> InEditor) : FApplicationMode("PanelDesigner", GetLocalizedUIDesignerMode)
{
	UE_LOG(LogTemp, Warning, TEXT("📌 PanelDesignerMode registered"));

	TabLayout = FTabManager::NewLayout("PanelDesigner_DefaultLayout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->Split(
					FTabManager::NewStack()
					->AddTab("UIBuilderPreview", ETabState::OpenedTab)
					->AddTab("UIBuilderVariables", ETabState::OpenedTab)
					->SetSizeCoefficient(0.2f)
				)
				->Split(
					FTabManager::NewStack()
					->AddTab("UIBuilderGraph", ETabState::OpenedTab)
					->SetSizeCoefficient(0.6f)
				)
				->Split(
					FTabManager::NewStack()
					->AddTab("UIBuilderSelection", ETabState::OpenedTab)
					->SetSizeCoefficient(0.2f)
				)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetHideTabWell(false)
				->SetSizeCoefficient(0.15f)
			)
		);
	WeakEditor = InEditor;
}

//TODO : move the actual registration back to the tab helper class. or maybe just remove it alltogether and leave registration here- idk yet
void FUIDesignerMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	UE_LOG(LogTemp, Warning, TEXT("✅ RegisterTabFactories called for UIDesignerMode"));

	if (TSharedPtr<FUIDesignerBlueprintEditor> Editor = WeakEditor.Pin())
	{
		UE_LOG(LogTemp, Warning, TEXT("✅ RegisterTabFactories Editor is valid"));

		TWeakPtr<FUIDesignerBlueprintEditor> LocalWeakEditor = Editor;

		InTabManager->RegisterTabSpawner("UIBuilderGraph", FOnSpawnTab::CreateLambda([LocalWeakEditor](const FSpawnTabArgs& Args)
			{
				if (TSharedPtr<FUIDesignerBlueprintEditor> EditorPinned = LocalWeakEditor.Pin())
				{
					UE_LOG(LogTemp, Warning, TEXT("🚀 Spawning UIBuilderGraph tab"));
					return SNew(SDockTab)
						.Label(FText::FromString("UI Builder Graph"))
						.TabRole(ETabRole::PanelTab)
						[
							SNew(STextBlock).Text(FText::FromString("[Graph Editor Placeholder]"))
						];
				}
				return SNew(SDockTab).Label(FText::FromString("Graph Error"));
			})).SetDisplayName(FText::FromString("UI Builder Graph"));
		InTabManager->RegisterTabSpawner("UIBuilderPreview", FOnSpawnTab::CreateLambda([LocalWeakEditor](const FSpawnTabArgs& Args)
			{
				if (LocalWeakEditor.IsValid())
				{
					UE_LOG(LogTemp, Warning, TEXT("🚀 Spawning UIBuilderPreview tab"));
					return SNew(SDockTab)
						.Label(FText::FromString("UI Preview"))
						.TabRole(ETabRole::PanelTab)
						[
							SNew(STextBlock).Text(FText::FromString("[Preview Placeholder]"))
						];
				}
				return SNew(SDockTab).Label(FText::FromString("Preview Error"));
			})).SetDisplayName(FText::FromString("UI Preview"));
		InTabManager->RegisterTabSpawner("UIBuilderSelection", FOnSpawnTab::CreateLambda([LocalWeakEditor](const FSpawnTabArgs& Args)
			{
				if (LocalWeakEditor.IsValid())
				{
					UE_LOG(LogTemp, Warning, TEXT("🚀 Spawning UIBuilderSelection tab"));
					return SNew(SDockTab)
						.Label(FText::FromString("UI Selection"))
						.TabRole(ETabRole::PanelTab)
						[
							SNew(STextBlock).Text(FText::FromString("[Selection Panel Placeholder]"))
						];
				}
				return SNew(SDockTab).Label(FText::FromString("Selection Error"));
			})).SetDisplayName(FText::FromString("UI Selection"));
		InTabManager->RegisterTabSpawner("UIBuilderVariables", FOnSpawnTab::CreateLambda([LocalWeakEditor](const FSpawnTabArgs& Args)
			{
				if (LocalWeakEditor.IsValid())
				{
					UE_LOG(LogTemp, Warning, TEXT("🚀 Spawning UIBuilderVariables tab"));
					return SNew(SDockTab)
						.Label(FText::FromString("UI Variables"))
						.TabRole(ETabRole::PanelTab)
						[
							SNew(STextBlock).Text(FText::FromString("[Variable Panel Placeholder]"))
						];
				}
				return SNew(SDockTab).Label(FText::FromString("Variables Error"));
			})).SetDisplayName(FText::FromString("UI Variables"));
	}
	FApplicationMode::RegisterTabFactories(InTabManager);
}



