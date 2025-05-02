#include "Graph/UIBuilderEditorExtension.h"
#include "Graph/UIBuilderBlueprintExtension.h"
#include "Graph/UIBuilderGraphSchema.h"
#include "Graph/UIBuilderGraphSidebarAction.h"
#include "Framework/Docking/TabManager.h"
#include "Graph/UIBuilderGraph.h"
#include "Graph/UIBuilderEditor.h"
#include "Graph/UIBuilderGraph.h"
#include "UIBuilderSubsystem.h"
#include "GraphEditor.h" //weeeee
#include "BlueprintEditor.h"
#include "BlueprintEditorModule.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Docking/SDockTab.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Framework/Docking/LayoutExtender.h"



FUIBuilderEditorExtension::FUIBuilderEditorExtension(FBlueprintEditor* InBlueprintEditor)
{
    BlueprintEditor = InBlueprintEditor;
}

FUIBuilderEditorExtension::~FUIBuilderEditorExtension()
{
}

TSharedRef<FUIBuilderEditorExtension> FUIBuilderEditorExtension::CreateEditorExtension(FBlueprintEditor* InBlueprintEditor)
{
    TSharedRef<FUIBuilderEditorExtension> NewExtension = MakeShared<FUIBuilderEditorExtension>(InBlueprintEditor);
    NewExtension->InitializeBlueprintEditorTabs();
    return NewExtension;
}

// Called from OnBlueprintEditorOpened. 
void FUIBuilderEditorExtension::InitializeBlueprintEditorTabs()
{
    if (!BlueprintEditor)
    {
        UE_LOG(LogTemp, Error, TEXT("⚠️ UIBuilder: BlueprintEditor is null!"));
        return;
    }

    const FName TabID = "UIBuilderGraph";
    TSharedPtr<FTabManager> TabManager = BlueprintEditor->GetTabManager();

    if (!TabManager.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("⚠️ UIBuilder: Invalid TabManager."));
        return;
    }

    // Only register if needed
    if (!TabManager->HasTabSpawner(TabID))
    {
        RegisterGraphTab();
    }

    TabManager->TryInvokeTab(TabID);
}

// Registers Graph into tab manager if it doesn't exist.
void FUIBuilderEditorExtension::RegisterGraphTab()
{
    const FName TabID = "UIBuilderGraph";
    TSharedPtr<FTabManager> TabManager = BlueprintEditor->GetTabManager();

    if (!TabManager.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("UIBuilder: TabManager is invalid"));
        return;
    }

    if (!TabManager->HasTabSpawner(TabID))
    {
        static TSharedRef<FWorkspaceItem> UIBuilderCategory = FWorkspaceItem::NewGroup(
            NSLOCTEXT("UIBuilder", "WorkspaceCategory", "UI Builder")
        );

        TabManager->RegisterTabSpawner(TabID, FOnSpawnTab::CreateSP(SharedThis(this), &FUIBuilderEditorExtension::CreateGraphTab))
            .SetDisplayName(NSLOCTEXT("UIBuilderGraph", "TabTitle", "UI Builder Graph"))
            .SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"))
            .SetGroup(UIBuilderCategory);

        UE_LOG(LogTemp, Warning, TEXT("UIBuilder: Registered TabSpawner!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("⚠️ UIBuilder: TabSpawner already registered. Skipping re-registration."));
    }
}

// Constructs and returns the actual UI content for the tab (Slate).
TSharedRef<SDockTab> FUIBuilderEditorExtension::CreateGraphTab(const FSpawnTabArgs& Args)
{
    if (!BlueprintEditor)
    {
        UE_LOG(LogTemp, Error, TEXT("UIBuilder: BlueprintEditor pointer is null during tab spawn!"));
        return SNew(SDockTab)
            [
                SNew(STextBlock).Text(FText::FromString("Invalid Blueprint Editor!"))
            ];
    }

    UBlueprint* Blueprint = BlueprintEditor->GetBlueprintObj();
    if (!Blueprint || !Blueprint->GeneratedClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("UIBuilder: Invalid or uncompiled Blueprint."));
        return SNew(SDockTab)
            [
                SNew(STextBlock).Text(FText::FromString("Invalid Blueprint"))
            ];
    }

    if (UUIBuilderGraph* Graph = GetOrCreateGraph(Blueprint))
    {
        TSharedRef<FUIBuilderEditor> UIEditor = MakeShared<FUIBuilderEditor>();
        UIEditor->Init(BlueprintEditor, Graph);
        OwnedEditor = UIEditor;

        return SNew(SDockTab)
            .TabRole(ETabRole::DocumentTab)
            .Label(FText::FromString("UI Builder"))
            .ToolTipText(FText::FromString("UI Builder Graph Editor"))
            [
                UIEditor->BuildGraphWidget()
            ];
    }

    UE_LOG(LogTemp, Error, TEXT("UIBuilder: Graph was null even after injection."));
    return SNew(SDockTab)
        [
            SNew(STextBlock).Text(FText::FromString("No UIBuilderGraph found"))
        ];
}

// Ensures the UUIBuilderGraph exists and returns it — responsible for persistent graph data.
UUIBuilderGraph* FUIBuilderEditorExtension::GetOrCreateGraph(UBlueprint* Blueprint) const
{
    UUIBuilderBlueprintExtension* Extension = GetOrCreateBlueprintExtension(Blueprint);
    if (!Extension) return nullptr;

    if (!Extension->UIBuilderGraph)
    {
        Extension->UIBuilderGraph = NewObject<UUIBuilderGraph>(
            Extension,
            TEXT("UIBuilderGraph"),
            RF_Transactional
        );

        Extension->UIBuilderGraph->Schema = UUIBuilderGraphSchema::StaticClass();
        UE_LOG(LogTemp, Warning, TEXT("✅ UIBuilder is initialized inside Blueprint"));
    }

    return Extension->UIBuilderGraph;
}

// Actually hooks up the Blueprint to store the UI Builder
UUIBuilderBlueprintExtension* FUIBuilderEditorExtension::GetOrCreateBlueprintExtension(UBlueprint* Blueprint) const
{
    if (!Blueprint) return nullptr;

    for (UBlueprintExtension* Ext : Blueprint->GetExtensions())
    {
        if (UUIBuilderBlueprintExtension* Found = Cast<UUIBuilderBlueprintExtension>(Ext))
        {
            return Found;
        }
    }

    // Create if missing
    UUIBuilderBlueprintExtension* NewExt = NewObject<UUIBuilderBlueprintExtension>(Blueprint);
    Blueprint->AddExtension(NewExt);
    return NewExt;
}

