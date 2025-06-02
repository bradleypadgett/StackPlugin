#include "StackBlueprintTabFactories.h"
#include "Graph/StackBlueprintGraph.h"
#include "Widgets/Text/STextBlock.h"
#include "StackBlueprintEditor.h"
#include "StackBlueprintTabs.h"

#define LOCTEXT_NAMESPACE "StackBlueprint"



FDesignerGraphSummoner::FDesignerGraphSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp)
    : FWorkflowTabFactory(FStackBlueprintTabs::DesignerGraphID, InHostingApp)
{
    TabLabel = LOCTEXT("DesignerGraphLabel", "Designer");
    TabIcon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "UMGEditor.SwitchToDesigner");

    bIsSingleton = true;

    ViewMenuDescription = LOCTEXT("DesignerGraphLabel", "Designer Graph");
    ViewMenuTooltip = LOCTEXT("DesignerGraph_Tooltip", "Show Desiner Graph");
}

TSharedRef<SWidget> FDesignerGraphSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
    TSharedPtr<FStackBlueprintEditor> Editor = StaticCastSharedPtr<FStackBlueprintEditor>(HostingApp.Pin());
    UEdGraph* DesignerGraph = Cast<UEdGraph>(Editor->GetStackBlueprintGraph());

    FGraphAppearanceInfo AppearanceInfo;
    AppearanceInfo.CornerText = NSLOCTEXT("StackBlueprint", "DesignerGraphCornerText", "DESIGNER");

    SGraphEditor::FGraphEditorEvents GraphEvents;

    return SNew(SGraphEditor)
        .AdditionalCommands(Editor->GetToolkitCommands())
        .GraphToEdit(DesignerGraph)
        .Appearance(AppearanceInfo)
        .GraphEvents(GraphEvents)
        .IsEditable(true);
}

FSelectionSummoner::FSelectionSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp)
    : FWorkflowTabFactory(FStackBlueprintTabs::SelectionID, InHostingApp)
{
    TabLabel = LOCTEXT("SelectionTabLabel", "Details");
    TabIcon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details");

    bIsSingleton = true;

    ViewMenuDescription = LOCTEXT("SelectionTabLabel", "Details");
    ViewMenuTooltip = LOCTEXT("SelectionTabView_Tooltip", "Show Selection Details");
}

TSharedRef<SWidget> FSelectionSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
    if (TSharedPtr<FStackBlueprintEditor> Editor = StaticCastSharedPtr<FStackBlueprintEditor>(HostingApp.Pin())) 
    {
        return Editor->GetPlaceholderWidget();
    } 
    else 
    {
        return SNew(STextBlock).Text(FText::FromString(TEXT("Invalid Editor")));
    }
}

FVariableSummoner::FVariableSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp)
    : FWorkflowTabFactory(FStackBlueprintTabs::VariablesID, InHostingApp)
{
    TabLabel = LOCTEXT("VariableTabLabel", "Parameters");
    TabIcon = FSlateIcon(FSlateIcon(FName("NiagaraEditorStyle"), "Tab.Parameters"));

    bIsSingleton = true;

    ViewMenuDescription = LOCTEXT("VariableTabView", "Parameters");
    ViewMenuTooltip = LOCTEXT("VariableTabView_ToolTip", "Show Variables List");

}

TSharedRef<SWidget> FVariableSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
    TSharedPtr<FStackBlueprintEditor> Editor = StaticCastSharedPtr<FStackBlueprintEditor>(HostingApp.Pin());

    return Editor->GetPlaceholderWidget();
}

FPaletteSummoner::FPaletteSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp)
    : FWorkflowTabFactory(FStackBlueprintTabs::PaletteID, InHostingApp)
{
    TabLabel = LOCTEXT("PaletteTabLabel", "Palette");
    TabIcon = FSlateIcon(FName("UMGStyle"), "Palette.Icon");

    bIsSingleton = true;

    ViewMenuDescription = LOCTEXT("PaletteTabView", "Palette");
    ViewMenuTooltip = LOCTEXT("PaletteTabView_ToolTip", "Show Palette");

}

TSharedRef<SWidget> FPaletteSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
    TSharedPtr<FStackBlueprintEditor> Editor = StaticCastSharedPtr<FStackBlueprintEditor>(HostingApp.Pin());

    return Editor->GetPlaceholderWidget();
}

FPreviewSummoner::FPreviewSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp)
    : FWorkflowTabFactory(FStackBlueprintTabs::PreviewID, InHostingApp)
{
    TabLabel = LOCTEXT("PreviewTabLabel", "Preview");
    TabIcon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Viewports");

    bIsSingleton = true;

    ViewMenuDescription = LOCTEXT("PreviewTabView", "Preview");
    ViewMenuTooltip = LOCTEXT("PreviewTabView_ToolTip", "Show Panel Preview");

}

TSharedRef<SWidget> FPreviewSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
    TSharedPtr<FStackBlueprintEditor> Editor = StaticCastSharedPtr<FStackBlueprintEditor>(HostingApp.Pin());

    return Editor->GetPlaceholderWidget();
}



#undef LOCTEXT_NAMESPACE