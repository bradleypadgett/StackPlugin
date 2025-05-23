#include "PanelDesignerToolbar.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "WorkflowOrientedApp/SModeWidget.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "PanelDesignerBlueprintEditor.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SBoxPanel.h"



// Manually injects [Designer] & [Graph] toolbar buttons with old FExtender system for allowing buttons to stay out of the overflow menu & be right-justified.
void FPanelDesignerToolbar::RegisterToolbar(UBlueprint* InBlueprint, TSharedPtr<FPanelDesignerBlueprintEditor> InEditor)
{
    TWeakPtr<FPanelDesignerBlueprintEditor> WeakEditor = InEditor;

    if (!WeakEditor.Pin() || !InBlueprint) return;

    if (!FBlueprintEditorUtils::IsLevelScriptBlueprint(InBlueprint) && !FBlueprintEditorUtils::IsInterfaceBlueprint(InBlueprint) && !InBlueprint->bIsNewlyCreated)
    {
        TSharedRef<FExtender> Extender = MakeShared<FExtender>();

        Extender->AddToolBarExtension(
        "Asset",
        EExtensionHook::After,
        InEditor->GetToolkitCommands(),
        FToolBarExtensionDelegate::CreateLambda([WeakEditor](FToolBarBuilder&)
        {
            if (!WeakEditor.IsValid()) return;
            TSharedPtr<FPanelDesignerBlueprintEditor> Editor = WeakEditor.Pin();

            TAttribute<FName> GetActiveMode = TAttribute<FName>::Create([Editor]() 
            {
                return Editor.IsValid() ? Editor->GetCurrentMode() : NAME_None;
            });
            FOnModeChangeRequested SetActiveMode = FOnModeChangeRequested::CreateLambda([Editor](FName InMode) 
            {
                if (Editor.IsValid()) Editor->HandleCurrentMode(InMode);
            });
            Editor->AddToolbarWidget(
            SNew(SBorder)
                .BorderImage(FAppStyle::Get().GetBrush("ToolPanel.GroupBorder"))
                .HAlign(HAlign_Fill)
                .VAlign(VAlign_Fill)
                .Padding(FMargin(0.f, 0.f, 0.f, 0.f))
                [
                SNew(SHorizontalBox)
                    + SHorizontalBox::Slot()
                    .AutoWidth()
                    .Padding(FMargin(4.f, 0.f, 8.f, 0.f))
                    .VAlign(VAlign_Center)
                    [
                    SNew(SBox)
                        .HeightOverride(24)
                        [
                        SNew(SModeWidget, FText::FromString("Designer"), "PanelDesigner")
                            .OnGetActiveMode(GetActiveMode)
                            .OnSetActiveMode(SetActiveMode)
                            .IconImage(FAppStyle::GetBrush("UMGEditor.SwitchToDesigner"))
                        ]
                    ]
                + SHorizontalBox::Slot()
                .AutoWidth()
                .Padding(FMargin(2.f, 0.f, 10.f, 0.f))
                .VAlign(VAlign_Center)
                    [
                    SNew(SBox)
                        .HeightOverride(24)
                        [
                        SNew(SModeWidget, FText::FromString("Graph"), "GraphName")
                            .OnGetActiveMode(GetActiveMode)
                            .OnSetActiveMode(SetActiveMode)
                            .IconImage(FAppStyle::GetBrush("FullBlueprintEditor.SwitchToScriptingMode"))
                        ]
                    ]
                ]
            );
        }));
        InEditor->AddToolbarExtender(Extender);
    }
}