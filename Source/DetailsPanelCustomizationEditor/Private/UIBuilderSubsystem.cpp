#include "UIBuilderSubsystem.h"
#include "Graph/UIBuilderGraph.h"
#include "Graph/UIBuilderGraphSchema.h"
#include "Graph/UIBuilderGraphWidget.h"
#include "Graph/UIBuilderGraphController.h"
#include "UIBuilderTabRegistrar.h"
#include "UIBuilderBlueprintExtension.h"
#include "BlueprintEditorTabs.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "UObject/SavePackage.h"
#include "BlueprintEditor.h"
#include "Editor/EditorEngine.h"
#include "Editor.h"
#include "BlueprintEditorModes.h"
#include "WorkflowOrientedApp/SModeWidget.h"
#include "Containers/Ticker.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBox.h"
#include "Framework/Application/SlateApplication.h"



void UUIBuilderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    if (UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
    {
        // Earlier stage: inject buttons before layout is finalized
        AssetEditorSubsystem->OnEditorOpeningPreWidgets().AddUObject(this, &UUIBuilderSubsystem::OnEditorPreWidgets);

        // Standard stage: register tabs after the editor has fully opened
        AssetEditorSubsystem->OnAssetEditorOpened().AddUObject(this, &UUIBuilderSubsystem::OnBlueprintEditorOpened);

        UE_LOG(LogTemp, Warning, TEXT("UIBuilderSubsystem: Initialized and bound to OnEditorPreWidgets and OnBlueprintEditorOpened."));

        FBlueprintEditorModule& BlueprintEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>("Kismet");
    }
}

void UUIBuilderSubsystem::Deinitialize()
{
    if (UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
    {
        AssetEditorSubsystem->OnAssetEditorOpened().RemoveAll(this);
    }

    Super::Deinitialize();
}

// Inject our buttons into the SHorizontalBox inside SStandaloneAssetEditorToolkitHost toolbar — delayed via timer to ensure full layout
void UUIBuilderSubsystem::OnEditorPreWidgets(const TArray<UObject*>& Assets, IAssetEditorInstance* Instance)
{
    if (Assets.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("⏩ Skipping Toolbar injection — no asset found"));
        return;
    }

    UBlueprint* BP = Cast<UBlueprint>(Assets[0]);
    if (!BP || !BP->GeneratedClass || !BP->GeneratedClass->IsChildOf(AActor::StaticClass()))
    {
        UE_LOG(LogTemp, Warning, TEXT("⏩ Skipping Toolbar injection — not an AActor"));
        return;
    }

    {
        if (!Instance)
        {
            UE_LOG(LogTemp, Error, TEXT("❌ Invalid editor instance in OnEditorPreWidgets"));
            return;
        }

        FBlueprintEditor* BlueprintEditor = static_cast<FBlueprintEditor*>(Instance);
        if (!BlueprintEditor)
        {
            UE_LOG(LogTemp, Error, TEXT("❌ Could not cast to FBlueprintEditor in OnEditorPreWidgets"));
            return;
        }

        // Delay actual logic to allow layout to complete
        FTimerHandle DummyHandle;
        GEditor->GetTimerManager()->SetTimer(DummyHandle, FTimerDelegate::CreateLambda([BlueprintEditor]()
        {
            TSharedPtr<IToolkitHost> ToolkitHost = BlueprintEditor->GetToolkitHost();
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
                                        .OnGetActiveMode_Lambda([BlueprintEditor]() {
                                        return BlueprintEditor->GetCurrentMode();
                                            })
                                        .OnSetActiveMode_Lambda([BlueprintEditor](FName InMode) {
                                        BlueprintEditor->SetCurrentMode(InMode);
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
                                        .OnGetActiveMode_Lambda([BlueprintEditor]() {
                                        return BlueprintEditor->GetCurrentMode();
                                            })
                                        .OnSetActiveMode_Lambda([BlueprintEditor](FName InMode) {
                                        BlueprintEditor->SetCurrentMode(InMode);
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
}

/*
 * Called whenever a Blueprint editor window finishes opening.
 */
void UUIBuilderSubsystem::OnBlueprintEditorOpened(UObject* Asset)
{
    if (UBlueprint* BlueprintAsset = Cast<UBlueprint>(Asset))
    {
        IAssetEditorInstance* RawAsset = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->FindEditorForAsset(BlueprintAsset, false);

        if (!RawAsset)
        {
            UE_LOG(LogTemp, Warning, TEXT("⚠️ UIBuilderSubsystem: Could not find active editor for Blueprint %s"), *BlueprintAsset->GetName());
            return;
        }

        FBlueprintEditor* BlueprintEditor = static_cast<FBlueprintEditor*>(RawAsset);

        if (TabRegistrars.Contains(BlueprintEditor))
        {
            UE_LOG(LogTemp, Warning, TEXT("⚠️ UIBuilderSubsystem: Editor already registered inside Blueprint."));
            return;
        }

        // ✅ Register custom tabs
        TSharedPtr<FUIBuilderTabRegistrar> NewRegistrar = MakeShared<FUIBuilderTabRegistrar>(BlueprintEditor);
        NewRegistrar->InitializeBlueprintEditorTabs();

        TabRegistrars.Add(BlueprintEditor, NewRegistrar);

        UE_LOG(LogTemp, Warning, TEXT("✅ UIBuilderSubsystem: Registered TabRegistrar for Blueprint: %s"), *BlueprintAsset->GetName());
    }
}