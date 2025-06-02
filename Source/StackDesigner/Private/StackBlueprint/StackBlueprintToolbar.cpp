#include "StackBlueprintToolbar.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "WorkflowOrientedApp/SModeWidget.h"
#include "StackBlueprintEditor.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SBoxPanel.h"



// Injects [Designer] & [Graph] toolbar buttons with FExtender since this method allows buttons to stay out of the overflow menu & be right-justified.
TSharedPtr<FExtender> FStackBlueprintToolbar::RegisterToolbar(UBlueprint* InBlueprint, TSharedPtr<FStackBlueprintEditor> InEditor)
{
    TWeakPtr<FStackBlueprintEditor> WeakEditor = InEditor;

    TSharedRef<FExtender> Extender = MakeShared<FExtender>();

    Extender->AddToolBarExtension(
    "Asset",
    EExtensionHook::After,
    InEditor->GetToolkitCommands(),
    FToolBarExtensionDelegate::CreateLambda([WeakEditor](FToolBarBuilder&)
    {
        TSharedPtr<FStackBlueprintEditor> Editor = WeakEditor.Pin();
        if (!Editor.IsValid())
        {
            UE_LOG(LogTemp, Warning, TEXT("FStackBlueprintToolbar: Editor is invalid during RegisterToolbar"));
            return;
        }

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
                    SNew(SModeWidget, FText::FromString("Designer"), "StackBlueprint")
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
    return Extender;
}