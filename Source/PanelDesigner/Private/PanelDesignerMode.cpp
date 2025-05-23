#include "PanelDesignerMode.h"
#include "PanelDesignerBlueprintEditor.h"
#include "BlueprintEditorModes.h"
#include "PanelDesignerTabs.h"



// Initializes custom application mode. Extends [FBlueprintEditorUnifiedMode] for access to native Blueprint tabs
FPanelDesignerMode::FPanelDesignerMode(TSharedPtr<FPanelDesignerBlueprintEditor> InBlueprintEditor, FName InModeName, FText(*GetLocalizedMode)(const FName), const bool bRegisterViewport)
	: FBlueprintEditorUnifiedMode(InBlueprintEditor, InModeName, GetLocalizedMode, bRegisterViewport)
{
	WeakEditor = InBlueprintEditor;
	TabLayout = FPanelDesignerTabs::CreateDefaultLayout();
}

// Calls helper class to initialize tabs
void FPanelDesignerMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	if (TSharedPtr<FPanelDesignerBlueprintEditor> Editor = WeakEditor.Pin())
	{
		FPanelDesignerTabs::RegisterDesignerModeTabs(Editor.Get(), InTabManager);
	}
	FApplicationMode::RegisterTabFactories(InTabManager);
}

// Automatically invoked when application mode is opened. Attempts to re-load layout & regenerates graph tab if none are open.
void FPanelDesignerMode::PostActivateMode()
{
	FBlueprintEditorUnifiedMode::PostActivateMode();
	/*
	if (TSharedPtr<FPanelDesignerBlueprintEditor> Editor = WeakEditor.Pin())
	{
		TSharedPtr<FTabManager> TabManager = Editor->GetTabManager();

		TSharedRef<FTabManager::FLayout> LayoutToUse = FLayoutSaveRestore::LoadFromConfig(GEditorLayoutIni, TabLayout.ToSharedRef());


		//if (LayoutToUse->GetPrimaryArea().IsValid()) ? Editor->RestoreFromLayout(LayoutToUse) : Editor->RestoreFromLayout(TabLayout.ToSharedRef());

		if (LayoutToUse->GetPrimaryArea().IsValid())
		{
			Editor->RestoreFromLayout(LayoutToUse);
		}
		else
		{
			Editor->RestoreFromLayout(TabLayout.ToSharedRef());
		}
	}*/
}

/*
		if (!TabManager->FindExistingLiveTab(FName("PanelDesignerGraph")).IsValid() &&
			!TabManager->FindExistingLiveTab(FName("PanelDesignerSelection")).IsValid() &&
			!TabManager->FindExistingLiveTab(FName("PanelDesignerVariables")).IsValid() &&
			!TabManager->FindExistingLiveTab(FName("PanelDesignerPreview")).IsValid())
		{
			TabManager->RestoreFrom(TabLayout.ToSharedRef(), TSharedPtr<SWindow>());
			TabManager->CloseAllAreas();
			TabManager->TryInvokeTab(FName("PanelDesignerGraph"));
		}
		if (TSharedPtr<SDockTab> GraphTab = TabManager->FindExistingLiveTab(FName("PanelDesignerGraph")))
		{
			GraphTab->DrawAttention();
		}
	}
}*/

// Automatically invoked when application mode is closed. Saves layout for syncing between sessions & blueprints
void FPanelDesignerMode::PreDeactivateMode()
{/*
	if (TSharedPtr<FPanelDesignerBlueprintEditor> Editor = WeakEditor.Pin(); Editor.IsValid())
	{
		Editor->GetTabManager()->SavePersistentLayout();
	}*/
	FBlueprintEditorUnifiedMode::PreDeactivateMode();
}