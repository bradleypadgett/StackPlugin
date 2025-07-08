#include "Widgets/SStackNodeRoot.h"
#include "Widgets/SStackNodeEntries.h"
#include "StackNode.h"
#include "ViewModels/StackRoot.h"
#include "ViewModels/Editor/StackRootViewModel.h"
#include "ViewModels/Editor/StackSelectionViewModel.h"
#include "ViewModels/Editor/StackSystemViewModel.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/StackStyle.h"



#define LOCTEXT_NAMESPACE "SStackNodeRoot"

void SStackNodeRoot::Construct(const FArguments& InArgs, UStackNode* InNode)
{
	Node = InNode;
	GraphNode = InNode;
	if (Node->GetOwningSystem())
	{
		/*if (TSharedPtr<FStackSystemViewModel> SystemViewModel = (Node->GetOwningSystem()))
		{

			RootViewModel = GetOwn;
		}*/
	}

	// TO-DO ~ Replace this with a singleton registered editor module which'll nab the cached ViewModels. 
	//RootViewModel = Node->GetRootViewModel();
	//SelectionViewModel = Node->GetSelectionViewModel();

	if (!RootViewModel || !SelectionViewModel)
	{
		UE_LOG(LogTemp, Warning, TEXT("SStackNodeRoot: Missing ViewModel or SelectionViewModel."));
		return;
	}

	SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}

void SStackNodeRoot::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{

}



void SStackNodeRoot::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();

	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);
	this->GetOrAddSlot(ENodeZone::Center)
		[
			SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					CreateTitleWidget(NodeTitle)
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					CreateNodeContentArea()
				]
		];
}

TSharedRef<SWidget> SStackNodeRoot::CreateTitleWidget(TSharedPtr<SNodeTitle> NodeTitle)
{
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SNew(STextBlock)
				.Text(FText::FromString("Stack Node"))
				.TextStyle(FAppStyle::Get(), "Graph.Node.NodeTitle")
		];
}

TSharedRef<SWidget> SStackNodeRoot::CreateNodeContentArea()
{
	return CreateNodeStack();
}

TSharedRef<SWidget> SStackNodeRoot::CreateNodeStack()
{
	return SNew(SStackNodeEntries, *RootViewModel, *SelectionViewModel);
}

#undef LOCTEXT_NAMESPACE