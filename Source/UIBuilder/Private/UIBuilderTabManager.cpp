#include "UIBuilderTabManager.h"
#include "UIBuilderBlueprintExtension.h"
#include "BlueprintEditor.h"
#include "EdGraph/EdGraph.h"
#include "GraphEditor.h"

// I'll merge functions later. don't care right now just want it to work lol

void FUIBuilderTabManager::HandleDesignerMode(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension, FName InNewMode)
{
    TSharedPtr<FTabManager> TabManager = InBlueprintEditor->GetTabManager();
    if (!TabManager.IsValid()) return;

    CloseStoredDesignerTabs(InBlueprintEditor, InBlueprintExtension); // ❌ Make sure hanging tabs are closed

    CaptureGraphLayout(InBlueprintEditor, InBlueprintExtension); // 💾 Save Graph layout arrangement
    StoreOpenedGraphTabs(InBlueprintEditor, InBlueprintExtension); // 📚 Store which tabs were open
    CloseStoredGraphTabs(InBlueprintEditor, InBlueprintExtension); // ❌ Close those tabs

    ApplyDesignerLayout(InBlueprintEditor, InBlueprintExtension); // 🎨 Create custom Designer layout

}
void FUIBuilderTabManager::HandleGraphMode(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension, FName InNewMode)
{
    TSharedPtr<FTabManager> TabManager = InBlueprintEditor->GetTabManager();
    if (!TabManager.IsValid()) return;

    CaptureDesignerLayout(InBlueprintEditor, InBlueprintExtension); // 💾 Save Designer layout arrangement
    StoreOpenedDesignerTabs(InBlueprintEditor, InBlueprintExtension); // 📚 Store which tabs were open
    CloseStoredDesignerTabs(InBlueprintEditor, InBlueprintExtension); // ❌ Close those tabs

    ApplyGraphLayout(InBlueprintEditor, InBlueprintExtension); // 🎨 Create original Blueprint layout

}

void FUIBuilderTabManager::CaptureDesignerLayout(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension)
{
    if (!InBlueprintEditor || !InBlueprintExtension) return;

    TSharedPtr<FTabManager> TabManager = InBlueprintEditor->GetTabManager();
    if (!TabManager.IsValid()) return;

    // Capture the full layout as a serialized string
    TSharedRef<FTabManager::FLayout> Layout = TabManager->PersistLayout();
    InBlueprintExtension->CapturedDesignerLayoutString = Layout->ToString();
}
void FUIBuilderTabManager::CaptureGraphLayout(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension)
{
    if (!InBlueprintEditor || !InBlueprintExtension) return;

    TSharedPtr<FTabManager> TabManager = InBlueprintEditor->GetTabManager();
    if (!TabManager.IsValid()) return;

    // Capture the current layout *before* anything is closed
    TSharedRef<FTabManager::FLayout> Layout = TabManager->PersistLayout();
    InBlueprintExtension->CapturedGraphLayoutString = Layout->ToString();

   // UE_LOG(LogTemp, Warning, TEXT("📦 Captured Graph Layout String:\n%s"), *InBlueprintExtension->CapturedGraphLayoutString);

}

void FUIBuilderTabManager::StoreOpenedDesignerTabs(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension)
{
    if (!InBlueprintEditor || !InBlueprintExtension) return;

    TSharedPtr<FTabManager> TabManager = InBlueprintEditor->GetTabManager();
    if (!TabManager.IsValid()) return;

    TArray<FName> DesignerTabs = { "UIBuilderGraph", "UIBuilderPreview", "UIBuilderSelection", "UIBuilderVariables" };
    InBlueprintExtension->PreviouslyOpenTabs.Reset();

    for (FName TabId : DesignerTabs)
    {
        if (TabManager->FindExistingLiveTab(TabId).IsValid())
        {
            InBlueprintExtension->PreviouslyOpenTabs.Add(TabId);
        }
    }
}
void FUIBuilderTabManager::StoreOpenedGraphTabs(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension)
{
    if (!InBlueprintEditor || !InBlueprintExtension) return;

    TSharedPtr<FTabManager> TabManager = InBlueprintEditor->GetTabManager();
    if (!TabManager.IsValid()) return;

    TArray<FName> StaticBlueprintTabs = {
        "ConstructionScriptEditor", "MyBlueprint", "SCSViewport", "CompilerResults",
        "FindResults", "BookmarkList", "Inspector", "PaletteList", "ReplaceNodeReferences"
    };

    InBlueprintExtension->PreviouslyOpenTabs.Reset();

    for (FName TabId : StaticBlueprintTabs)
    {
        if (TabManager->FindExistingLiveTab(TabId).IsValid())
        {
            InBlueprintExtension->PreviouslyOpenTabs.Add(TabId);
        }
    }

    // 🔎 Just log how many LastEditedDocuments are active (they'll restore automatically)
    UE_LOG(LogTemp, Warning, TEXT("📘 %d open document graphs (LastEditedDocuments)"),
        InBlueprintEditor->GetBlueprintObj()->LastEditedDocuments.Num());
}

void FUIBuilderTabManager::CloseStoredDesignerTabs(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension)
{
    TSharedPtr<FTabManager> TabManager = InBlueprintEditor->GetTabManager();

    for (FName TabId : InBlueprintExtension->PreviouslyOpenTabs)
    {
        if (TSharedPtr<SDockTab> Tab = TabManager->FindExistingLiveTab(TabId))
        {
            CloseTabIfOpen(TabManager, TabId);
        }
    }
}
void FUIBuilderTabManager::CloseStoredGraphTabs(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension)
{
    if (!InBlueprintEditor || !InBlueprintExtension) return;

    // 🧼 Clear keyboard focus first
    FSlateApplication::Get().ClearKeyboardFocus(EFocusCause::Cleared);

    // 💣 Close all open document graph tabs (EventGraph, functions, macros, etc.)
    const TArray<FEditedDocumentInfo>& OpenDocs = InBlueprintEditor->GetBlueprintObj()->LastEditedDocuments;
    for (const FEditedDocumentInfo& DocInfo : OpenDocs)
    {
        if (UEdGraph* Graph = Cast<UEdGraph>(DocInfo.EditedObjectPath.ResolveObject()))
        {
            UE_LOG(LogTemp, Warning, TEXT("🧼 Closing graph tab: %s"), *Cast<UEdGraph>(DocInfo.EditedObjectPath.ResolveObject())->GetName());
            InBlueprintEditor->CloseDocumentTab(Cast<UEdGraph>(DocInfo.EditedObjectPath.ResolveObject()));
        }
    }

    // Optional: Clear auto-reopen list
    InBlueprintEditor->GetBlueprintObj()->LastEditedDocuments.Empty();

    // 🔒 Close remaining tabs like MyBlueprint or ConstructionScript
    TSharedPtr<FTabManager> TabManager = InBlueprintEditor->GetTabManager();
    for (FName TabId : InBlueprintExtension->PreviouslyOpenTabs)
    {
        if (TabId != "Document")
        {
            CloseTabIfOpen(TabManager, TabId);
        }
    }
}

void FUIBuilderTabManager::ApplyDesignerLayout(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension)
{
    TSharedPtr<FTabManager> TabManager = InBlueprintEditor->GetTabManager();
    if (!TabManager.IsValid()) {
        UE_LOG(LogTemp, Error, TEXT("❌ TabManager is invalid in ApplyDesignerLayout"));
        return;
    }

    // 📐 Always generate a fresh layout
    int32 Version = ++InBlueprintExtension->DesignerLayoutRestoreCount;
    FName LayoutName = FName(*FString::Printf(TEXT("UIBuilder_DesignerLayout_v%d"), Version));

    UE_LOG(LogTemp, Warning, TEXT("🧱 Building layout: %s"), *LayoutName.ToString());

    TSharedPtr<FTabManager::FLayout> Layout = FTabManager::NewLayout(LayoutName)
        ->AddArea(
            FTabManager::NewPrimaryArea()
            ->SetOrientation(Orient_Horizontal)
            ->Split(
                FTabManager::NewSplitter()
                ->SetOrientation(Orient_Vertical)
                ->Split(
                    FTabManager::NewStack()
                    ->AddTab("UIBuilderPreview", ETabState::OpenedTab)
                    ->SetHideTabWell(false)
                    ->SetSizeCoefficient(0.5f)
                )
                ->Split(
                    FTabManager::NewStack()
                    ->AddTab("UIBuilderVariables", ETabState::OpenedTab)
                    ->SetHideTabWell(false)
                    ->SetSizeCoefficient(0.5f)
                )
                ->SetSizeCoefficient(0.25f)
            )
            ->Split(
                FTabManager::NewSplitter()
                ->SetOrientation(Orient_Vertical)
                ->Split(
                    FTabManager::NewStack()
                    ->AddTab("UIBuilderGraph", ETabState::OpenedTab)
                    ->SetHideTabWell(false)
                    ->SetSizeCoefficient(0.6f)
                )
                ->Split(
                    FTabManager::NewStack()
                    ->AddTab("UIBuilderSelection", ETabState::OpenedTab)
                    ->SetHideTabWell(false)
                    ->SetSizeCoefficient(0.4f)
                )
                ->SetSizeCoefficient(0.75f)
            )
        );

    // 💾 Save layout string for debug (optional)
    InBlueprintExtension->CapturedDesignerLayoutString = Layout->ToString();
    UE_LOG(LogTemp, Warning, TEXT("🧩 Layout string saved:\n%s"), *InBlueprintExtension->CapturedDesignerLayoutString);

    // 🕒 Delay restore by one tick
    TFunction<void()> RestoreCallback = [TabManager, Layout, InBlueprintEditor]()
        {
            if (!TabManager.IsValid()) {
                UE_LOG(LogTemp, Error, TEXT("❌ TabManager is invalid inside RestoreCallback"));
                return;
            }
            UE_LOG(LogTemp, Warning, TEXT("🪄 Restoring Designer layout now"));

            TSharedPtr<SWindow> HostWindow = FSlateApplication::Get().FindWidgetWindow(
                InBlueprintEditor->GetToolkitHost()->GetParentWidget());

            if (!HostWindow.IsValid()) {
                UE_LOG(LogTemp, Error, TEXT("❌ HostWindow is invalid during RestoreCallback"));
                return;
            }

            TabManager->RestoreFrom(Layout.ToSharedRef(), HostWindow);

            // 🧪 Post-restore TryInvokeTab test
            FTSTicker::GetCoreTicker().AddTicker(
                FTickerDelegate::CreateLambda([TabManager](float)
                    {
                        UE_LOG(LogTemp, Warning, TEXT("🧪 Post-restore TryInvokeTab test"));
                        TabManager->TryInvokeTab(FName("UIBuilderPreview"));
                        TabManager->TryInvokeTab(FName("UIBuilderVariables"));
                        TabManager->TryInvokeTab(FName("UIBuilderGraph"));
                        TabManager->TryInvokeTab(FName("UIBuilderSelection"));
                        return false;
                    }),
                1.0f);
        };

    FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateLambda([RestoreCallback](float)
            {
                UE_LOG(LogTemp, Warning, TEXT("🕐 Executing deferred RestoreCallback"));
                RestoreCallback();
                return false; // one-shot
            }),
        0.0f
    );
}









void FUIBuilderTabManager::ApplyGraphLayout(FBlueprintEditor* InBlueprintEditor, UUIBuilderBlueprintExtension* InBlueprintExtension)
{
    if (!InBlueprintEditor || !InBlueprintExtension) return;

    if (InBlueprintExtension->CapturedGraphLayoutString.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("⚠️ CapturedGraphLayoutString is empty."));
        return;
    }

    TSharedPtr<FTabManager::FLayout> Layout = FTabManager::FLayout::NewFromString(InBlueprintExtension->CapturedGraphLayoutString);
    if (!Layout.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("❌ Failed to parse CapturedGraphLayoutString into a layout."));
        return;
    }

    TSharedPtr<SWindow> Window = FSlateApplication::Get().FindWidgetWindow(
        InBlueprintEditor->GetToolkitHost()->GetParentWidget());

    TSharedPtr<FTabManager> TabManager = InBlueprintEditor->GetTabManager();
    if (!TabManager.IsValid()) return;

    // 🧪 Re-open only non-UIBuilder tabs
    for (FName TabId : InBlueprintExtension->PreviouslyOpenTabs)
    {
        if (TabId.ToString().StartsWith("UIBuilder"))
        {
            UE_LOG(LogTemp, Warning, TEXT("⛔ Skipping UIBuilder tab during Graph restore: %s"), *TabId.ToString());
            continue;
        }

        if (!TabManager->FindExistingLiveTab(TabId).IsValid())
        {
            TabManager->TryInvokeTab(TabId);
        }
    }

    // 🔄 Restore the captured Blueprint layout
    TabManager->RestoreFrom(Layout.ToSharedRef(), Window);
}



TArray<FName> FUIBuilderTabManager::GetOpenTabIDs(TSharedPtr<FTabManager> InTabManager, const TArray<FName>& InKnownTabs)
{
    TArray<FName> Result;

    for (FName TabId : InKnownTabs)
    {
        if (InTabManager->FindExistingLiveTab(TabId).IsValid())
        {
            Result.Add(TabId);
        }
    }

    return Result;
}
void FUIBuilderTabManager::CloseTabIfOpen(TSharedPtr<FTabManager> InTabManager, FName InTabId)
{
    TSharedPtr<SDockTab> Tab = InTabManager->FindExistingLiveTab(InTabId);
    if (Tab.IsValid())
    {
        Tab->RequestCloseTab();
    }
}



