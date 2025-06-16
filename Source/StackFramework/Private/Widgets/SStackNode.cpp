#include "Widgets/SStackNode.h"
#include "Widgets/SStackView.h"
#include "StackNode.h"
#include "ViewModels/Editor/StackViewModel.h"
#include "ViewModels/Editor/StackSelectionViewModel.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/StackStyle.h"



#define LOCTEXT_NAMESPACE "SStackNode"

void SStackNode::Construct(const FArguments& InArgs, UStackNode* InNode)
{
	StackNode = InNode;
	GraphNode = InNode;

	StackViewModel = StackNode->GetStackViewModel();
	if (!StackViewModel)
	{
		UE_LOG(LogTemp, Warning, TEXT("SStackNode: StackViewModel is null!"));
		return;
	}

	SelectionViewModel = StackViewModel->GetSelectionViewModel();
	if (!SelectionViewModel)
	{
		UE_LOG(LogTemp, Warning, TEXT("SStackNode: SelectionViewModel is null!"));
	}

	SetCursor(EMouseCursor::CardinalCross);

	UpdateGraphNode();
}

void SStackNode::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SGraphNode::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	// Add visual tick updates here later (selection highlight, etc.)
}

TSharedRef<SWidget> SStackNode::CreateNodeContentArea()
{
	return SNew(SStackView)
		.StackViewModel(StackViewModel)
		.SelectionViewModel(SelectionViewModel);
}


#undef LOCTEXT_NAMESPACE
