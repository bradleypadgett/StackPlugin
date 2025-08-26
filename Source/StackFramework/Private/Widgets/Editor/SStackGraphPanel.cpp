#include "Widgets/Editor/SStackGraphPanel.h"
#include "Widgets/SCompoundWidget.h"
#include "Editor/StackGraph.h"
#include "Editor/StackGraphSchema.h"
#include "ViewModels/Editor/StackSystemManager.h"
#include "GraphEditorActions.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"


/*
void SStackGraphPanel::Construct(const FArguments& InArgs)
{
	SystemManager = InArgs._SystemManager;

	// Create an empty StackGraph asset to visualize (you’ll replace this later)
	UStackGraph* Graph = NewObject<UStackGraph>();

	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = NSLOCTEXT("Stack", "GraphCornerText", "Stack View");

	ChildSlot
		[
			SAssignNew(GraphEditor, SGraphEditor)
				.GraphToEdit(Graph)
				.Appearance(AppearanceInfo)
				.ShowGraphStateOverlay(false)
				.OnCreateActionMenu(FOnCreateActionMenu::CreateSP(this, &SStackGraphPanel::CreateContextMenu))
		];
}

TSharedRef<SWidget> SStackGraphPanel::CreateContextMenu()
{
	FMenuBuilder MenuBuilder(true, nullptr);

	MenuBuilder.BeginSection("StackContext", LOCTEXT("StackContextSection", "Stack"));
	{
		MenuBuilder.AddMenuEntry(
			LOCTEXT("AddStack", "Add Stack..."),
			LOCTEXT("AddStackTooltip", "Adds a new stack to the system."),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateSP(this, &SStackGraphPanel::HandleAddStack))
		);
	}
	MenuBuilder.EndSection();

	return MenuBuilder.MakeWidget();
}

FReply SStackGraphPanel::HandleAddStack()
{
	if (SystemManager.IsValid())
	{
		SystemManager->AddNewStack();
	}
	return FReply::Handled();
}
*/