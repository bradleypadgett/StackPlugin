#include "Graph/UIBuilderBlueprintExtension.h"
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



FUIBuilderBlueprintExtension::FUIBuilderBlueprintExtension(FBlueprintEditor* InBlueprintEditor)
{
    BlueprintEditor = InBlueprintEditor;
}

FUIBuilderBlueprintExtension::~FUIBuilderBlueprintExtension()
{
}

TSharedRef<FUIBuilderBlueprintExtension> FUIBuilderBlueprintExtension::Create(FBlueprintEditor* InBlueprintEditor)
{
    TSharedRef<FUIBuilderBlueprintExtension> NewExtension = MakeShared<FUIBuilderBlueprintExtension>(InBlueprintEditor);
    NewExtension->ExtendBlueprintEditor();
    return NewExtension;
}

void FUIBuilderBlueprintExtension::ExtendBlueprintEditor()
{
    if (!BlueprintEditor)
    {
        UE_LOG(LogTemp, Error, TEXT("UIBuilder: BlueprintEditor pointer is null! Cannot extend."));
        return;
    }

    const FName TabID = "UIBuilderGraph";
    TSharedPtr<FTabManager> TabManager = BlueprintEditor->GetTabManager();

    if (!TabManager.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("UIBuilder: Failed to get TabManager from Blueprint Editor!"));
        return;
    }

    // Inject the graph now that we’re inside the full Blueprint editor
    if (UUIBuilderSubsystem* Subsystem = GEditor->GetEditorSubsystem<UUIBuilderSubsystem>())
    {
        UBlueprint* Blueprint = BlueprintEditor->GetBlueprintObj();
        Subsystem->InjectGraphHolder(Blueprint);
    }

    // Only register the tab if it's not already registered
    if (!TabManager->HasTabSpawner(TabID))
    {
        static TSharedRef<FWorkspaceItem> UIBuilderCategory = FWorkspaceItem::NewGroup(
            NSLOCTEXT("UIBuilder", "WorkspaceCategory", "UI Builder")
        );

        TabManager->RegisterTabSpawner(TabID, FOnSpawnTab::CreateSP(SharedThis(this), &FUIBuilderBlueprintExtension::SpawnUIBuilderGraphTab))
            .SetDisplayName(NSLOCTEXT("UIBuilderGraph", "TabTitle", "UI Builder Graph"))
            .SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"))
            .SetGroup(UIBuilderCategory);

        UE_LOG(LogTemp, Warning, TEXT("UIBuilder: Registered TabSpawner!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("⚠️ UIBuilder: TabSpawner already registered. Skipping re-registration."));
    }
    TabManager->TryInvokeTab(TabID);
}

TSharedRef<SDockTab> FUIBuilderBlueprintExtension::SpawnUIBuilderGraphTab(const FSpawnTabArgs& Args)
{
    if (!BlueprintEditor)
    {
        UE_LOG(LogTemp, Error, TEXT("UIBuilder: BlueprintEditor pointer is null during tab spawn!"));
        return SNew(SDockTab)
            [
                SNew(STextBlock).Text(FText::FromString(TEXT("Invalid Blueprint Editor!")))
            ];
    }

    UBlueprint* Blueprint = BlueprintEditor->GetBlueprintObj();
    if (!Blueprint || !Blueprint->GeneratedClass)
    {
        return SNew(SDockTab)
            [
                SNew(STextBlock).Text(FText::FromString(TEXT("Invalid Blueprint!")))
            ];
    }

    // At this point, the full Blueprint editor is open, so it's not data-only anymore
    if (UUIBuilderSubsystem* Subsystem = GEditor->GetEditorSubsystem<UUIBuilderSubsystem>())
    {
        Subsystem->InjectGraphHolderInstance(Blueprint); // Ensures graph holder exists

        if (UUIBuilderGraph* Graph = Subsystem->GetGraphForBlueprint(Blueprint))
        {
            TSharedRef<FUIBuilderEditor> UIEditor = MakeShared<FUIBuilderEditor>();
            UIEditor->Init(BlueprintEditor, Graph);
            OwnedEditor = UIEditor;

            // Create the actual tab
            TSharedRef<SDockTab> Tab = SNew(SDockTab)
                .TabRole(ETabRole::DocumentTab)
                .Label(FText::FromString("UI Builder"))
                .ToolTipText(FText::FromString("UI Builder Graph Editor"))
                .Content()
                [
                    UIEditor->BuildGraphWidget()
                ];
            return Tab;
        }
    }

    return SNew(SDockTab)
        [
            SNew(STextBlock).Text(FText::FromString(TEXT("No UIBuilderGraph found.")))
        ];
}
