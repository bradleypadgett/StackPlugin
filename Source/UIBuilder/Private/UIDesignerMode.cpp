#include "UIDesignerMode.h"
#include "UIDesignerBlueprintEditor.h"
#include "UIDesignerTabs.h"



static FText GetLocalizedUIDesignerMode(FName InMode)
{
	return FText::FromString("UI Designer");
}

FUIDesignerMode::FUIDesignerMode(TSharedPtr<FUIDesignerBlueprintEditor> InEditor) : FApplicationMode("PanelDesigner", GetLocalizedUIDesignerMode)
{
	WeakEditor = InEditor;
	TabLayout = FUIDesignerTabs::CreateDefaultLayout();
}

void FUIDesignerMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	UE_LOG(LogTemp, Warning, TEXT("✅ RegisterTabFactories called for UIDesignerMode"));

	if (TSharedPtr<FUIDesignerBlueprintEditor> Editor = WeakEditor.Pin())
	{
		FUIDesignerTabs::RegisterDesignerModeTabs(Editor.Get(), InTabManager);
	}

	FApplicationMode::RegisterTabFactories(InTabManager);
}

void FUIDesignerMode::PostActivateMode()
{

	if (TSharedPtr<FUIDesignerBlueprintEditor> Editor = WeakEditor.Pin())
	{
		TSharedPtr<FTabManager> TabManager = Editor->GetTabManager();

		if (!TabManager->FindExistingLiveTab(FName("UIBuilderGraph")).IsValid() &&
			!TabManager->FindExistingLiveTab(FName("UIBuilderSelection")).IsValid() &&
			!TabManager->FindExistingLiveTab(FName("UIBuilderVariables")).IsValid() &&
			!TabManager->FindExistingLiveTab(FName("UIBuilderPreview")).IsValid())
		{
			TabManager->TryInvokeTab(FName("UIBuilderGraph"));
		}
	}
}

void FUIDesignerMode::PreDeactivateMode()
{
	if (TSharedPtr<FUIDesignerBlueprintEditor> Editor = WeakEditor.Pin(); Editor.IsValid())
	{
		Editor->GetTabManager()->SavePersistentLayout();
	}
}

