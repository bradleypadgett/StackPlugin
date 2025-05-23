#include "PanelDesignerMode.h"
#include "PanelDesignerBlueprintEditor.h"
#include "PanelDesignerTabs.h"
#include "BlueprintEditorModes.h"



static FText GetLocalizedPanelDesignerMode(FName InMode)
{
	return FText::FromString("UI Designer");
}

FPanelDesignerMode::FPanelDesignerMode(TSharedPtr<FPanelDesignerBlueprintEditor> InBlueprintEditor, FName InModeName, FText(*GetLocalizedMode)(const FName), const bool bRegisterViewport)
	: FBlueprintEditorUnifiedMode(InBlueprintEditor, InModeName, GetLocalizedMode, bRegisterViewport)
{
	WeakEditor = InBlueprintEditor;
	TabLayout = FPanelDesignerTabs::CreateDefaultLayout();
}

void FPanelDesignerMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	UE_LOG(LogTemp, Warning, TEXT("✅ RegisterTabFactories called for PanelDesignerMode"));

	if (TSharedPtr<FPanelDesignerBlueprintEditor> Editor = WeakEditor.Pin())
	{
		FPanelDesignerTabs::RegisterDesignerModeTabs(Editor.Get(), InTabManager);
	}

	FApplicationMode::RegisterTabFactories(InTabManager);
}

void FPanelDesignerMode::PostActivateMode()
{

	if (TSharedPtr<FPanelDesignerBlueprintEditor> Editor = WeakEditor.Pin())
	{
		TSharedPtr<FTabManager> TabManager = Editor->GetTabManager();

		if (!TabManager->FindExistingLiveTab(FName("PanelDesignerGraph")).IsValid() &&
			!TabManager->FindExistingLiveTab(FName("PanelDesignerSelection")).IsValid() &&
			!TabManager->FindExistingLiveTab(FName("PanelDesignerVariables")).IsValid() &&
			!TabManager->FindExistingLiveTab(FName("PanelDesignerPreview")).IsValid())
		{
//			TSharedRef<FTabManager::FLayout> DefaultLayout = FPanelDesignerTabs::CreateDefaultLayout();
//			TSharedRef<FTabManager> TabManager = Editor->GetTabManager().ToSharedRef();
//			TabManager->RestoreFrom(DefaultLayout, TSharedPtr<SWindow>());

			TabManager->TryInvokeTab(FName("PanelDesignerGraph"));

		}
		//if (TSharedPtr<SDockTab> GraphTab = TabManager->FindExistingLiveTab(FName("PanelDesignerGraph")))
		//{
		//	GraphTab->DrawAttention();
		//}
	}
}

void FPanelDesignerMode::PreDeactivateMode()
{
	if (TSharedPtr<FPanelDesignerBlueprintEditor> Editor = WeakEditor.Pin(); Editor.IsValid())
	{
		Editor->GetTabManager()->SavePersistentLayout();
	}
}

