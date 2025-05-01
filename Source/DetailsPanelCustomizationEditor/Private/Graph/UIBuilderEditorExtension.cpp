#include "Graph/UIBuilderEditorExtension.h"
#include "Graph/UIBuilderBlueprintExtension.h"
#include "Graph/UIBuilderGraphSchema.h"
#include "Graph/UIBuilderGraphSidebarAction.h"
#include "Framework/Docking/TabManager.h"
#include "Graph/UIBuilderGraphHolder.h"
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
    NewExtension->ExtendBlueprintEditor();
    return NewExtension;
}

// Called from OnBlueprintEditorOpened. 
void FUIBuilderEditorExtension::ExtendBlueprintEditor()
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

        TabManager->RegisterTabSpawner(TabID, FOnSpawnTab::CreateSP(SharedThis(this), &FUIBuilderEditorExtension::CreateUIBuilderGraphTab))
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

// Creates the Graph tab after registering, lives inside tab manager. 
TSharedRef<SDockTab> FUIBuilderEditorExtension::CreateUIBuilderGraphTab(const FSpawnTabArgs& Args)
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

// Creates the actual Graph
UUIBuilderGraph* FUIBuilderEditorExtension::GetOrCreateGraph(UBlueprint* Blueprint) const
{
    UUIBuilderBlueprintExtension* Extension = GetOrCreateBlueprintExtension(Blueprint);
    if (!Extension) return nullptr;

    if (!Extension->GraphHolder)
    {
        Extension->GraphHolder = NewObject<UUIBuilderGraphHolder>(Extension, TEXT("UIBuilderGraph_Holder"), RF_Public | RF_Transactional);
    }

    if (!Extension->GraphHolder->UIBuilderGraph)
    {
        Extension->GraphHolder->UIBuilderGraph = NewObject<UUIBuilderGraph>(
            Extension->GraphHolder,
            TEXT("UIBuilderGraph"),
            RF_Transactional
        );

        Extension->GraphHolder->UIBuilderGraph->Schema = UUIBuilderGraphSchema::StaticClass();
        UE_LOG(LogTemp, Warning, TEXT("✅ Created UIBuilderGraph inside new/existing holder."));
    }

    return Extension->GraphHolder->UIBuilderGraph;
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

