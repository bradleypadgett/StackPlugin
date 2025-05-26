#include "PanelDesignerTabFactories.h"
#include "PanelDesignerExtension.h"
#include "Graph/PanelDesignerGraphEditor.h"
#include "Graph/PanelDesignerGraph.h"
#include "GraphEditorModule.h"
#include "Framework/Docking/TabManager.h"
#include "PanelDesignerEditor.h"
#include "Widgets/Text/STextBlock.h"
#include "PanelDesignerTabs.h"

#define LOCTEXT_NAMESPACE "PanelDesigner"



FDesignerGraphSummoner::FDesignerGraphSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp)
    : FWorkflowTabFactory(FPanelDesignerTabs::DesignerGraphID, InHostingApp)
{
    TabLabel = LOCTEXT("DesignerGraphLabel", "Designer");
    TabIcon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "UMGEditor.SwitchToDesigner");

    bIsSingleton = true;

    ViewMenuDescription = LOCTEXT("DesignerGraphLabel", "Designer Graph");
    ViewMenuTooltip = LOCTEXT("DesignerGraph_Tooltip", "Show Desiner Graph");
}

TSharedRef<SWidget> FDesignerGraphSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
    TSharedPtr<FPanelDesignerEditor> Editor = StaticCastSharedPtr<FPanelDesignerEditor>(HostingApp.Pin());
    UEdGraph* DesignerGraph = Cast<UEdGraph>(Editor->GetPanelDesignerGraph());

    FGraphAppearanceInfo AppearanceInfo;
    AppearanceInfo.CornerText = NSLOCTEXT("PanelDesigner", "DesignerGraphCornerText", "DESIGNER");

    SGraphEditor::FGraphEditorEvents GraphEvents;

    return SNew(SGraphEditor)
        .AdditionalCommands(Editor->GetToolkitCommands())
        .GraphToEdit(DesignerGraph)
        .Appearance(AppearanceInfo)
        .GraphEvents(GraphEvents)
        .IsEditable(true);
}

FSelectionSummoner::FSelectionSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp)
    : FWorkflowTabFactory(FPanelDesignerTabs::SelectionID, InHostingApp)
{
    TabLabel = LOCTEXT("SelectionTabLabel", "Details");
    TabIcon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details");

    bIsSingleton = true;

    ViewMenuDescription = LOCTEXT("SelectionTabLabel", "Details");
    ViewMenuTooltip = LOCTEXT("SelectionTabView_Tooltip", "Show Selection Details");
}
//////////
TSharedRef<SWidget> FSelectionSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
    if (TSharedPtr<FPanelDesignerEditor> Editor = StaticCastSharedPtr<FPanelDesignerEditor>(HostingApp.Pin())) 
    {
        return Editor->GetPlaceholderWidget();
    } 
    else 
    {
        return SNew(STextBlock).Text(FText::FromString(TEXT("Invalid Editor")));
    }
}

FVariableSummoner::FVariableSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp)
    : FWorkflowTabFactory(FPanelDesignerTabs::VariablesID, InHostingApp)
{
    TabLabel = LOCTEXT("VariableTabLabel", "Parameters");
    TabIcon = FSlateIcon(FSlateIcon(FName("NiagaraEditorStyle"), "Tab.Parameters"));

    bIsSingleton = true;

    ViewMenuDescription = LOCTEXT("VariableTabView", "Parameters");
    ViewMenuTooltip = LOCTEXT("VariableTabView_ToolTip", "Show Variables List");

}

TSharedRef<SWidget> FVariableSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
    TSharedPtr<FPanelDesignerEditor> Editor = StaticCastSharedPtr<FPanelDesignerEditor>(HostingApp.Pin());

    return Editor->GetPlaceholderWidget();
}

FPaletteSummoner::FPaletteSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp)
    : FWorkflowTabFactory(FPanelDesignerTabs::PaletteID, InHostingApp)
{
    TabLabel = LOCTEXT("PaletteTabLabel", "Palette");
    TabIcon = FSlateIcon(FName("UMGStyle"), "Palette.Icon");

    bIsSingleton = true;

    ViewMenuDescription = LOCTEXT("PaletteTabView", "Palette");
    ViewMenuTooltip = LOCTEXT("PaletteTabView_ToolTip", "Show Palette");

}

TSharedRef<SWidget> FPaletteSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
    TSharedPtr<FPanelDesignerEditor> Editor = StaticCastSharedPtr<FPanelDesignerEditor>(HostingApp.Pin());

    return Editor->GetPlaceholderWidget();
}


FPreviewSummoner::FPreviewSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp)
    : FWorkflowTabFactory(FPanelDesignerTabs::PreviewID, InHostingApp)
{
    TabLabel = LOCTEXT("PreviewTabLabel", "Preview");
    TabIcon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Viewports");

    bIsSingleton = true;

    ViewMenuDescription = LOCTEXT("PreviewTabView", "Preview");
    ViewMenuTooltip = LOCTEXT("PreviewTabView_ToolTip", "Show Panel Preview");

}

TSharedRef<SWidget> FPreviewSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
    TSharedPtr<FPanelDesignerEditor> Editor = StaticCastSharedPtr<FPanelDesignerEditor>(HostingApp.Pin());

    return Editor->GetPlaceholderWidget();
}



/*

// Register each tab individually if not already registered
void FPanelDesignerTabFactories::RegisterDesignerModeTabs(FPanelDesignerEditor* InBlueprint, TSharedPtr<FTabManager> InTabManager)
{
    UPanelDesignerExtension* Extension = InBlueprint->GetExtension();

    TSharedRef<FWorkspaceItem> LocalCategory = InTabManager->GetLocalWorkspaceMenuRoot()->AddGroup(NSLOCTEXT("PanelDesigner", "WorkspacePanelDesigner", "Panel Designer"));

    RegisterDefaultTabs(InTabManager, LocalCategory);

    

    
    if (!InTabManager->FindTabSpawnerFor("PanelDesignerGraph").IsValid()) RegisterGraphEditor(InTabManager, LocalCategory, Extension);
    if (!InTabManager->FindTabSpawnerFor("PanelDesignerPreview").IsValid()) RegisterPreviewTab(InTabManager, LocalCategory);
    if (!InTabManager->FindTabSpawnerFor("PanelDesignerSelection").IsValid()) RegisterSelectionTab(InTabManager, LocalCategory);
    if (!InTabManager->FindTabSpawnerFor("PanelDesignerVariables").IsValid()) RegisterVariableTab(InTabManager, LocalCategory);
    
}

// TODO: add in some default tabs like 'Find Result' that'd be useful in this appmode too!
void FPanelDesignerTabFactories::RegisterDefaultTabs(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory)
{

}

// Registers graph tab for storing nodes.
void FPanelDesignerTabFactories::RegisterGraphEditor(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory, UPanelDesignerExtension* InExtension)
{
    InTabManager->RegisterTabSpawner("PanelDesignerGraph", FOnSpawnTab::CreateLambda([InTabManager, InExtension](const FSpawnTabArgs& Args)
    {
    return SNew(SDockTab)
        .Label(FText::FromString("Designer Graph"))
        .TabRole(ETabRole::PanelTab)
        [
            SNew(SPanelDesignerGraphEditor).GraphToEdit(InExtension->GetPanelDesignerGraph())
        ];
    }))
    .SetDisplayName(FText::FromString("Designer Graph"))
    .SetGroup(InLocalCategory);
}

// Registers preview tab for displaying panel changes.
void FPanelDesignerTabFactories::RegisterPreviewTab(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory)
{
    InTabManager->RegisterTabSpawner("PanelDesignerPreview", FOnSpawnTab::CreateLambda([InTabManager](const FSpawnTabArgs& Args)
    {
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

// Registers selection tab for handling edits in the stacks.
void FPanelDesignerTabFactories::RegisterSelectionTab(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory)
{
    InTabManager->RegisterTabSpawner("PanelDesignerSelection", FOnSpawnTab::CreateLambda([InTabManager](const FSpawnTabArgs& Args)
    {
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

// Registers variable tab for giving access to native Blueprint variables.
void FPanelDesignerTabFactories::RegisterVariableTab(TSharedPtr<FTabManager> InTabManager, TSharedRef<FWorkspaceItem> InLocalCategory)
{
    InTabManager->RegisterTabSpawner("PanelDesignerVariables", FOnSpawnTab::CreateLambda([InTabManager](const FSpawnTabArgs& Args)
    {
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

// Creates default layout for new engine sessions
TSharedRef<FTabManager::FLayout> FPanelDesignerTabFactories::CreateDefaultLayout()
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
}*/

#undef LOCTEXT_NAMESPACE