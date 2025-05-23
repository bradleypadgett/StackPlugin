#include "PanelDesignerTabs.h"
#include "Framework/Docking/TabManager.h"
#include "PanelDesignerBlueprintExtension.h"
#include "Graph/PanelDesignerGraphEditor.h"
#include "PanelDesignerBlueprintEditor.h"
#include "Widgets/Text/STextBlock.h"
#include "Graph/PanelDesignerGraph.h"
#include "BlueprintEditor.h"

  

// Register each tab individually if not already registered
void FPanelDesignerTabs::RegisterDesignerModeTabs(FPanelDesignerBlueprintEditor* InBlueprint, TSharedPtr<FTabManager> InTabManager)
{
    UE_LOG(LogTemp, Warning, TEXT("🧩 Registering tab: PanelDesignerGraph to TabManager: %p"), InTabManager.Get());

    UPanelDesignerBlueprintExtension* Extension = InBlueprint->GetExtension();

    TSharedRef<FWorkspaceItem> LocalCategory = InTabManager->GetLocalWorkspaceMenuRoot()->AddGroup(
        NSLOCTEXT("PanelDesigner", "WorkspacePanelDesigner", "Panel Designer"));

    RegisterDefaultTabs(InTabManager, LocalCategory);

    if (!InTabManager->FindTabSpawnerFor("PanelDesignerGraph").IsValid()) RegisterGraphEditor(InTabManager, LocalCategory, Extension);
    if (!InTabManager->FindTabSpawnerFor("PanelDesignerPreview").IsValid()) RegisterPreviewTab(InTabManager, LocalCategory);
    if (!InTabManager->FindTabSpawnerFor("PanelDesignerSelection").IsValid()) RegisterSelectionTab(InTabManager, LocalCategory);
    if (!InTabManager->FindTabSpawnerFor("PanelDesignerVariables").IsValid()) RegisterVariableTab(InTabManager, LocalCategory);

}

void FPanelDesignerTabs::RegisterDefaultTabs(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory)
{
    //TODO: add in some default tabs like 'Find Result' that'd be useful in this appmode too!
}

void FPanelDesignerTabs::RegisterGraphEditor(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory, UPanelDesignerBlueprintExtension* InExtension)
{
    InTabManager->RegisterTabSpawner("PanelDesignerGraph", FOnSpawnTab::CreateLambda([InTabManager, InExtension](const FSpawnTabArgs& Args)
    {
    UE_LOG(LogTemp, Warning, TEXT("🚀 Spawning PanelDesignerGraph tab"));

    UPanelDesignerGraph* Graph = InExtension ? InExtension->EnsurePanelDesignerGraph() : nullptr;

    return SNew(SDockTab)
        .Label(FText::FromString("Designer Graph"))
        .TabRole(ETabRole::PanelTab)
        [
            SNew(SPanelDesignerGraphEditor).GraphToEdit(Graph)
        ];
    }))
    .SetDisplayName(FText::FromString("Designer Graph"))
    .SetGroup(InLocalCategory);
}

void FPanelDesignerTabs::RegisterPreviewTab(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory)
{
    InTabManager->RegisterTabSpawner("PanelDesignerPreview", FOnSpawnTab::CreateLambda([InTabManager](const FSpawnTabArgs& Args)
        {
            UE_LOG(LogTemp, Warning, TEXT("🚀 Spawning PanelDesignerPreview tab"));

            return SNew(SDockTab)
                .Label(FText::FromString("Panel Preview"))
                .TabRole(ETabRole::PanelTab)
                [
                    SNew(STextBlock).Text(FText::FromString("[Preview Placeholder]"))
                ];
        }))
        .SetDisplayName(FText::FromString("Panel Preview"))
        .SetGroup(InLocalCategory);
}

void FPanelDesignerTabs::RegisterSelectionTab(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory)
{
    InTabManager->RegisterTabSpawner("PanelDesignerSelection", FOnSpawnTab::CreateLambda([InTabManager](const FSpawnTabArgs& Args)
        {
            UE_LOG(LogTemp, Warning, TEXT("🚀 Spawning PanelDesignerSelection tab"));

            return SNew(SDockTab)
                .Label(FText::FromString("Panel Selection"))
                .TabRole(ETabRole::PanelTab)
                [
                    SNew(STextBlock).Text(FText::FromString("[Selection Panel Placeholder]"))
                ];
        }))
        .SetDisplayName(FText::FromString("Panel Selection"))
        .SetGroup(InLocalCategory);
}

void FPanelDesignerTabs::RegisterVariableTab(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory)
{
    InTabManager->RegisterTabSpawner("PanelDesignerVariables", FOnSpawnTab::CreateLambda([InTabManager](const FSpawnTabArgs& Args)
        {
            UE_LOG(LogTemp, Warning, TEXT("🚀 Spawning PanelDesignerVariables tab"));

            return SNew(SDockTab)
                .Label(FText::FromString("Panel Variables"))
                .TabRole(ETabRole::PanelTab)
                [
                    SNew(STextBlock).Text(FText::FromString("[Variable Panel Placeholder]"))
                ];
        }))
        .SetDisplayName(FText::FromString("Panel Variables"))
        .SetGroup(InLocalCategory);
}

TSharedRef<FTabManager::FLayout> FPanelDesignerTabs::CreateDefaultLayout()
{
    return FTabManager::NewLayout("PanelDesigner_DefaultLayout_v1")
        ->AddArea(
            FTabManager::NewPrimaryArea()
            ->SetOrientation(Orient_Vertical)
            ->Split(
                FTabManager::NewSplitter()
                ->SetOrientation(Orient_Horizontal)

                // LEFT SIDE
                ->Split(
                    FTabManager::NewSplitter()
                    ->SetOrientation(Orient_Vertical)
                    ->Split(
                        FTabManager::NewStack()
                        ->AddTab("UIBuilderSelection", ETabState::OpenedTab)
                        ->SetSizeCoefficient(0.5f)
                    )
                    ->Split(
                        FTabManager::NewStack()
                        ->AddTab("UIBuilderVariables", ETabState::OpenedTab)
                        ->SetSizeCoefficient(0.5f)
                    )
                    ->SetSizeCoefficient(0.2f)
                )

                // CENTER
                ->Split(
                    FTabManager::NewStack()
                    ->AddTab("UIBuilderGraph", ETabState::OpenedTab)
                    ->SetSizeCoefficient(0.6f)
                )

                // RIGHT SIDE
                ->Split(
                    FTabManager::NewStack()
                    ->AddTab("UIBuilderPreview", ETabState::OpenedTab)
                    ->SetSizeCoefficient(0.2f)
                )
            )
            ->Split(
                FTabManager::NewStack()
                ->AddTab("FindResults", ETabState::ClosedTab)
                ->SetSizeCoefficient(0.2f)
            )
        );
}