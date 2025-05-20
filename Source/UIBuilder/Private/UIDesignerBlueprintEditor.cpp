#include "UIDesignerBlueprintEditor.h"
#include "UIDesignerMode.h"
#include "BlueprintEditor.h"
#include "BlueprintEditorModes.h"
#include "UIBuilderBlueprintExtension.h"
#include "UIDesignerTabs.h"



FName FUIDesignerBlueprintEditor::GetEditorAppName()
{
	static const FName AppName(TEXT("UIDesignerBlueprintEditor"));
	return AppName;
}

void FUIDesignerBlueprintEditor::PostInitAssetEditor()
{
    FBlueprintEditor::PostInitAssetEditor();

}

void FUIDesignerBlueprintEditor::CreateEditor(EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& ToolkitHost, UBlueprint* Blueprint)
{
	TSharedRef<FUIDesignerBlueprintEditor> Editor = MakeShared<FUIDesignerBlueprintEditor>();

	const bool bShouldOpenInDefaultsMode = false;
	UE_LOG(LogTemp, Warning, TEXT("!Trying to register Appmodes"));
	Editor->InitBlueprintEditor(Mode, ToolkitHost, { Blueprint }, bShouldOpenInDefaultsMode);
	Editor->InitUIDesignerMode(Mode, ToolkitHost, Blueprint);

}

void FUIDesignerBlueprintEditor::InitUIDesignerMode(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UBlueprint* Blueprint)
{

	TSharedRef<FUIDesignerMode> DesignerMode = MakeShareable(new FUIDesignerMode(SharedThis(this)));

	UE_LOG(LogTemp, Warning, TEXT("🔍 TabManager is %s"), GetTabManager() ? TEXT("VALID") : TEXT("NULL"));

	AddApplicationMode("PanelDesigner", DesignerMode);

	DesignerMode->RegisterTabFactories(GetTabManager());

	const TSharedRef<FTabManager::FLayout> Layout = DesignerMode->GetTabLayout().ToSharedRef();
	const TSharedPtr<SWindow> HostingWindow = FSlateApplication::Get().FindWidgetWindow(AsShared()->GetToolkitHost()->GetParentWidget());

	if (HostingWindow.IsValid())
	{
		GetTabManager()->RestoreFrom(Layout, HostingWindow);
	}
}
