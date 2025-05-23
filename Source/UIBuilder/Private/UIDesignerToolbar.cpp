#include "UIDesignerToolbar.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "WorkflowOrientedApp/SModeWidget.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "UIDesignerBlueprintEditor.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SBoxPanel.h"



void FUIDesignerToolbar::RegisterToolbar(UBlueprint* InBlueprint, TSharedPtr<FUIDesignerBlueprintEditor> InEditor)
{
    UE_LOG(LogTemp, Warning, TEXT("🧹 RegisterToolbar Called!"));

    TWeakPtr<FUIDesignerBlueprintEditor> WeakEditor = InEditor;

    if (WeakEditor.Pin()) UE_LOG(LogTemp, Warning, TEXT("✅ Blueprint editor is valid!"));
    if (InBlueprint)  UE_LOG(LogTemp, Warning, TEXT("✅ Blueprint is valid!"));;

    if (!WeakEditor.Pin() || !InBlueprint) return;
    UE_LOG(LogTemp, Warning, TEXT("✅ Editor and Blueprint are valid!"));

    if (!FBlueprintEditorUtils::IsLevelScriptBlueprint(InBlueprint)) UE_LOG(LogTemp, Warning, TEXT("✅ Blueprint isnt a level script BP"));
    if (!FBlueprintEditorUtils::IsInterfaceBlueprint(InBlueprint)) UE_LOG(LogTemp, Warning, TEXT("✅ Blueprint isnt an interface BP"));
    if (!InBlueprint->bIsNewlyCreated)  UE_LOG(LogTemp, Warning, TEXT("✅ Blueprint isnt newly created"));

    if (!FBlueprintEditorUtils::IsLevelScriptBlueprint(InBlueprint) && !FBlueprintEditorUtils::IsInterfaceBlueprint(InBlueprint) && !InBlueprint->bIsNewlyCreated)
    {
        UE_LOG(LogTemp, Warning, TEXT("🧹 Trying to create Toolbar!"));
        TSharedRef<FExtender> Extender = MakeShared<FExtender>();

        Extender->AddToolBarExtension(
        "Asset",
        EExtensionHook::After,
        InEditor->GetToolkitCommands(),
        FToolBarExtensionDelegate::CreateLambda([WeakEditor](FToolBarBuilder&)
            {
                if (!WeakEditor.IsValid()) return;
                TSharedPtr<FUIDesignerBlueprintEditor> Editor = WeakEditor.Pin();

                TAttribute<FName> GetActiveMode = TAttribute<FName>::Create([Editor]() {
                    return Editor.IsValid() ? Editor->GetCurrentMode() : NAME_None;
                    });
                FOnModeChangeRequested SetActiveMode = FOnModeChangeRequested::CreateLambda([Editor](FName InMode) {
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
            })
        );
        InEditor->AddToolbarExtender(Extender);
    }
}