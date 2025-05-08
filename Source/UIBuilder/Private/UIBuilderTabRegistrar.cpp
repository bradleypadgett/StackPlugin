#include "UIBuilderTabRegistrar.h"
#include "UIBuilderBlueprintExtension.h"
#include "Graph/UIBuilderGraphSchema.h"
#include "Graph/UIBuilderGraphSidebarAction.h"
#include "Framework/Docking/TabManager.h"
#include "Graph/UIBuilderGraph.h"
#include "Graph/UIBuilderGraphController.h"
#include "UIBuilderSubsystem.h"
#include "GraphEditor.h" //weeeee
#include "BlueprintEditor.h"
#include "BlueprintEditorModes.h"
#include "BlueprintEditorModule.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Docking/SDockTab.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Framework/Docking/LayoutExtender.h"
#include "Containers/Ticker.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBox.h"
#include "Framework/Application/SlateApplication.h"
#include "WorkflowOrientedApp/SModeWidget.h"



FUIBuilderTabRegistrar::FUIBuilderTabRegistrar()
{

}

FUIBuilderTabRegistrar::~FUIBuilderTabRegistrar()
{

}

// Called from OnBlueprintEditorOpened. 
void FUIBuilderTabRegistrar::InitializeBlueprintEditorTabs(FBlueprintEditor* InBlueprintEditor)
{
    if (!InBlueprintEditor)
    {
        UE_LOG(LogTemp, Error, TEXT("⚠️ UIBuilder: BlueprintEditor is null!"));
        return;
    }

    const FName TabID = "UIBuilderGraph";
    TSharedPtr<FTabManager> TabManager = InBlueprintEditor->GetTabManager();

    if (!TabManager.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("⚠️ UIBuilder: Invalid TabManager."));
        return;
    }

    // Only register if needed
    if (!TabManager->HasTabSpawner(TabID))
    {
        RegisterGraphTab(InBlueprintEditor);
    }

    TabManager->TryInvokeTab(TabID);
}

// Registers Graph into tab manager if it doesn't exist.
void FUIBuilderTabRegistrar::RegisterGraphTab(FBlueprintEditor* InBlueprintEditor)
{

}

// Inject buttons into the SHorizontalBox inside SStandaloneAssetEditorToolkitHost toolbar — delayed via timer to ensure full layout
void FUIBuilderTabRegistrar::InjectModeSwitcherToolbar(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InExtension)
{
    // Delay actual logic to allow layout to complete
    FTimerHandle DummyHandle;
    GEditor->GetTimerManager()->SetTimer(DummyHandle, FTimerDelegate::CreateLambda([InBlueprintEditor, InExtension]()
        {

            TSharedPtr<IToolkitHost> ToolkitHost = InBlueprintEditor->GetToolkitHost();
            if (!ToolkitHost.IsValid())
            {
                UE_LOG(LogTemp, Error, TEXT("❌ Invalid toolkit host after delay"));
                return;
            }

            TSharedPtr<SWindow> Window = FSlateApplication::Get().FindWidgetWindow(ToolkitHost->GetParentWidget());
            if (!Window.IsValid())
            {
                UE_LOG(LogTemp, Error, TEXT("❌ Could not find SWindow after delay"));
                return;
            }

            TSharedPtr<SHorizontalBox> TargetBox;

            TFunction<void(const TSharedRef<SWidget>&)> FindFirstBoxInEditorHost;
            FindFirstBoxInEditorHost = [&FindFirstBoxInEditorHost, &TargetBox](const TSharedRef<SWidget>& Widget)
                {
                    if (Widget->GetTypeAsString() == "SHorizontalBox")
                    {
                        TargetBox = StaticCastSharedRef<SHorizontalBox>(Widget);
                        UE_LOG(LogTemp, Warning, TEXT("🎯 Found SHorizontalBox inside editor host!"));
                        return;
                    }

                    const FChildren* Children = Widget->GetChildren();
                    if (Children)
                    {
                        for (int32 i = 0; i < Children->Num(); ++i)
                        {
                            const TSharedRef<const SWidget> ChildConst = Children->GetChildAt(i);
                            const TSharedRef<SWidget> Child = StaticCastSharedRef<SWidget>(ConstCastSharedRef<SWidget>(ChildConst));
                            FindFirstBoxInEditorHost(Child);
                            if (TargetBox.IsValid()) return;
                        }
                    }
                };

            TFunction<void(const TSharedRef<SWidget>&)> FindEditorHost;
            FindEditorHost = [&FindEditorHost, &FindFirstBoxInEditorHost](const TSharedRef<SWidget>& Widget)
                {
                    if (Widget->GetTypeAsString().Contains("SStandaloneAssetEditorToolkitHost"))
                    {
                        UE_LOG(LogTemp, Display, TEXT("🔍 Found SStandaloneAssetEditorToolkitHost — taking first SHorizontalBox inside"));
                        FindFirstBoxInEditorHost(Widget);
                        return;
                    }

                    const FChildren* Children = Widget->GetChildren();
                    if (Children)
                    {
                        for (int32 i = 0; i < Children->Num(); ++i)
                        {
                            const TSharedRef<const SWidget> ChildConst = Children->GetChildAt(i);
                            const TSharedRef<SWidget> Child = StaticCastSharedRef<SWidget>(ConstCastSharedRef<SWidget>(ChildConst));
                            FindEditorHost(Child);
                        }
                    }
                };

            FindEditorHost(Window.ToSharedRef());

            if (!TargetBox.IsValid())
            {
                UE_LOG(LogTemp, Error, TEXT("❌ Could not find SHorizontalBox inside SStandaloneAssetEditorToolkitHost (after delay)"));
                return;
            }

            TWeakObjectPtr<UUIBuilderBlueprintExtension> WeakExt = InExtension;

            TSharedRef<SWidget> InjectedButtons =
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
                                    SNew(SModeWidget, FText::FromString("Designer"), "Designer")
                                        .OnGetActiveMode_Lambda([WeakExt]() -> FName {
                                        return WeakExt.IsValid() ? WeakExt->GetCurrentMode() : FName();
                                            })
                                        .OnSetActiveMode_Lambda([WeakExt](FName InMode) {
                                        if (WeakExt.IsValid()) { WeakExt->SetCurrentMode(InMode); }
                                            })
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
                                    SNew(SModeWidget, FText::FromString("Graph"), "Graph")
                                        .OnGetActiveMode_Lambda([WeakExt]() -> FName {
                                        return WeakExt.IsValid() ? WeakExt->GetCurrentMode() : FName();
                                            })
                                        .OnSetActiveMode_Lambda([WeakExt](FName InMode) {
                                        if (WeakExt.IsValid()) { WeakExt->SetCurrentMode(InMode); }
                                            })
                                        .IconImage(FAppStyle::GetBrush("FullBlueprintEditor.SwitchToScriptingMode"))
                                ]
                        ]
                ];
            // Inject into the toolbar
            TargetBox->AddSlot()
                .AutoWidth()
                .VAlign(VAlign_Fill)
                [
                    InjectedButtons
                ];

            UE_LOG(LogTemp, Warning, TEXT("✅ Buttons injected into SHorizontalBox inside SStandaloneAssetEditorToolkitHost (after delay)!"));
        }),
        0.05f, false);
}


/*
void FUIBuilderTabRegistrar::InjectModeSwitcherToolbar(FBlueprintEditor* InBlueprintEditor)
{
    // Delay actual logic to allow layout to complete
    FTimerHandle DummyHandle;
    GEditor->GetTimerManager()->SetTimer(DummyHandle, FTimerDelegate::CreateLambda([InBlueprintEditor]()
        {
            
            TSharedPtr<IToolkitHost> ToolkitHost = InBlueprintEditor->GetToolkitHost();
            if (!ToolkitHost.IsValid())
            {
                UE_LOG(LogTemp, Error, TEXT("❌ Invalid toolkit host after delay"));
                return;
            }

            TSharedPtr<SWindow> Window = FSlateApplication::Get().FindWidgetWindow(ToolkitHost->GetParentWidget());
            if (!Window.IsValid())
            {
                UE_LOG(LogTemp, Error, TEXT("❌ Could not find SWindow after delay"));
                return;
            }

            TSharedPtr<SHorizontalBox> TargetBox;

            TFunction<void(const TSharedRef<SWidget>&)> FindFirstBoxInEditorHost;
            FindFirstBoxInEditorHost = [&FindFirstBoxInEditorHost, &TargetBox](const TSharedRef<SWidget>& Widget)
                {
                    if (Widget->GetTypeAsString() == "SHorizontalBox")
                    {
                        TargetBox = StaticCastSharedRef<SHorizontalBox>(Widget);
                        UE_LOG(LogTemp, Warning, TEXT("🎯 Found SHorizontalBox inside editor host!"));
                        return;
                    }

                    const FChildren* Children = Widget->GetChildren();
                    if (Children)
                    {
                        for (int32 i = 0; i < Children->Num(); ++i)
                        {
                            const TSharedRef<const SWidget> ChildConst = Children->GetChildAt(i);
                            const TSharedRef<SWidget> Child = StaticCastSharedRef<SWidget>(ConstCastSharedRef<SWidget>(ChildConst));
                            FindFirstBoxInEditorHost(Child);
                            if (TargetBox.IsValid()) return;
                        }
                    }
                };

            TFunction<void(const TSharedRef<SWidget>&)> FindEditorHost;
            FindEditorHost = [&FindEditorHost, &FindFirstBoxInEditorHost](const TSharedRef<SWidget>& Widget)
                {
                    if (Widget->GetTypeAsString().Contains("SStandaloneAssetEditorToolkitHost"))
                    {
                        UE_LOG(LogTemp, Display, TEXT("🔍 Found SStandaloneAssetEditorToolkitHost — taking first SHorizontalBox inside"));
                        FindFirstBoxInEditorHost(Widget);
                        return;
                    }

                    const FChildren* Children = Widget->GetChildren();
                    if (Children)
                    {
                        for (int32 i = 0; i < Children->Num(); ++i)
                        {
                            const TSharedRef<const SWidget> ChildConst = Children->GetChildAt(i);
                            const TSharedRef<SWidget> Child = StaticCastSharedRef<SWidget>(ConstCastSharedRef<SWidget>(ChildConst));
                            FindEditorHost(Child);
                        }
                    }
                };

            FindEditorHost(Window.ToSharedRef());

            if (!TargetBox.IsValid())
            {
                UE_LOG(LogTemp, Error, TEXT("❌ Could not find SHorizontalBox inside SStandaloneAssetEditorToolkitHost (after delay)"));
                return;
            }

            TSharedRef<SWidget> InjectedButtons =
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
                                    SNew(SModeWidget, FText::FromString("Designer"), "UIBuilderDesigner")
                                        .OnGetActiveMode_Lambda([InBlueprintEditor]() {
                                        return InBlueprintEditor->GetCurrentMode();
                                            })
                                        .OnSetActiveMode_Lambda([InBlueprintEditor](FName InMode) {
                                        InBlueprintEditor->SetCurrentMode(InMode);
                                            })
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
                                    SNew(SModeWidget, FText::FromString("Graph"), FBlueprintEditorApplicationModes::StandardBlueprintEditorMode)
                                        .OnGetActiveMode_Lambda([InBlueprintEditor]() {
                                        return InBlueprintEditor->GetCurrentMode();
                                            })
                                        .OnSetActiveMode_Lambda([InBlueprintEditor](FName InMode) {
                                        InBlueprintEditor->SetCurrentMode(InMode);
                                            })
                                        .IconImage(FAppStyle::GetBrush("FullBlueprintEditor.SwitchToScriptingMode"))
                                ]
                        ]
                ];

            // Inject into the toolbar
            TargetBox->AddSlot()
                .AutoWidth()
                .VAlign(VAlign_Fill)
                [
                    InjectedButtons
                ];

            UE_LOG(LogTemp, Warning, TEXT("✅ Buttons injected into SHorizontalBox inside SStandaloneAssetEditorToolkitHost (after delay)!"));
        }),
        0.05f, false);
}
*/