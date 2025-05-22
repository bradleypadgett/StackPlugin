#include "UIDesignerTabs.h"
#include "Framework/Docking/TabManager.h"
#include "UIBuilderBlueprintExtension.h"
#include "Graph/UIBuilderGraphEditor.h"
#include "UIDesignerBlueprintEditor.h"
#include "Widgets/Text/STextBlock.h"
#include "Graph/UIBuilderGraph.h"
#include "BlueprintEditor.h"



// Register each tab individually if not already registered
void FUIDesignerTabs::RegisterDesignerModeTabs(FUIDesignerBlueprintEditor* InBlueprint, TSharedPtr<FTabManager> InTabManager)
{
    UE_LOG(LogTemp, Warning, TEXT("🧩 Registering tab: UIBuilderGraph to TabManager: %p"), InTabManager.Get());

    UUIBuilderBlueprintExtension* Extension = InBlueprint->GetExtension();

    TSharedRef<FWorkspaceItem> LocalCategory = InTabManager->GetLocalWorkspaceMenuRoot()->AddGroup(
        NSLOCTEXT("PanelDesigner", "WorkspacePanelDesigner", "Panel Designer"));

    RegisterDefaultTabs(InTabManager, LocalCategory);

    if (!InTabManager->FindTabSpawnerFor("UIBuilderGraph").IsValid()) RegisterGraphEditor(InTabManager, LocalCategory, Extension);
    if (!InTabManager->FindTabSpawnerFor("UIBuilderPreview").IsValid()) RegisterPreviewTab(InTabManager, LocalCategory);
    if (!InTabManager->FindTabSpawnerFor("UIBuilderSelection").IsValid()) RegisterSelectionTab(InTabManager, LocalCategory);
    if (!InTabManager->FindTabSpawnerFor("UIBuilderVariables").IsValid()) RegisterVariableTab(InTabManager, LocalCategory);

}

void FUIDesignerTabs::RegisterDefaultTabs(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory)
{
    //TODO: add in some default tabs like 'Find Result' that'd be useful in this appmode too!
}

void FUIDesignerTabs::RegisterGraphEditor(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory, UUIBuilderBlueprintExtension* InExtension)
{
    InTabManager->RegisterTabSpawner("UIBuilderGraph", FOnSpawnTab::CreateLambda([InTabManager, InExtension](const FSpawnTabArgs& Args)
    {
    UE_LOG(LogTemp, Warning, TEXT("🚀 Spawning UIBuilderGraph tab"));

    UUIBuilderGraph* Graph = InExtension ? InExtension->EnsureUIBuilderGraph() : nullptr;

    return SNew(SDockTab)
        .Label(FText::FromString("UI Builder Graph"))
        .TabRole(ETabRole::PanelTab)
        [
            SNew(SUIBuilderGraphEditor).GraphToEdit(Graph)
        ];
    }))
    .SetDisplayName(FText::FromString("UI Builder Graph"))
    .SetGroup(InLocalCategory);
}

void FUIDesignerTabs::RegisterPreviewTab(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory)
{
    InTabManager->RegisterTabSpawner("UIBuilderPreview", FOnSpawnTab::CreateLambda([InTabManager](const FSpawnTabArgs& Args)
        {
            UE_LOG(LogTemp, Warning, TEXT("🚀 Spawning UIBuilderPreview tab"));

            return SNew(SDockTab)
                .Label(FText::FromString("UI Preview"))
                .TabRole(ETabRole::PanelTab)
                [
                    SNew(STextBlock).Text(FText::FromString("[Preview Placeholder]"))
                ];
        }))
        .SetDisplayName(FText::FromString("UI Preview"))
        .SetGroup(InLocalCategory);
}

void FUIDesignerTabs::RegisterSelectionTab(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory)
{
    InTabManager->RegisterTabSpawner("UIBuilderSelection", FOnSpawnTab::CreateLambda([InTabManager](const FSpawnTabArgs& Args)
        {
            UE_LOG(LogTemp, Warning, TEXT("🚀 Spawning UIBuilderSelection tab"));

            return SNew(SDockTab)
                .Label(FText::FromString("UI Selection"))
                .TabRole(ETabRole::PanelTab)
                [
                    SNew(STextBlock).Text(FText::FromString("[Selection Panel Placeholder]"))
                ];
        }))
        .SetDisplayName(FText::FromString("UI Selection"))
        .SetGroup(InLocalCategory);
}

void FUIDesignerTabs::RegisterVariableTab(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory)
{
    InTabManager->RegisterTabSpawner("UIBuilderVariables", FOnSpawnTab::CreateLambda([InTabManager](const FSpawnTabArgs& Args)
        {
            UE_LOG(LogTemp, Warning, TEXT("🚀 Spawning UIBuilderVariables tab"));

            return SNew(SDockTab)
                .Label(FText::FromString("UI Variables"))
                .TabRole(ETabRole::PanelTab)
                [
                    SNew(STextBlock).Text(FText::FromString("[Variable Panel Placeholder]"))
                ];
        }))
        .SetDisplayName(FText::FromString("UI Variables"))
        .SetGroup(InLocalCategory);
}

TSharedRef<FTabManager::FLayout> FUIDesignerTabs::CreateDefaultLayout()
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