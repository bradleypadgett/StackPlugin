#include "ViewModels/Editor/StackEditorViewModel.h"
#include "ViewModels/Editor/StackViewModel.h"
#include "StackNode.h"
#include "Widgets/SBoxPanel.h"



FStackEditorViewModel::FStackEditorViewModel()
{

}

void FStackEditorViewModel::AddStackNode(UStackNode* Node)
{
	if (Node)
	{
		StackNodes.AddUnique(Node);
	}
}

TArray<UStackNode*> FStackEditorViewModel::GetAllNodes() const
{
	TArray<UStackNode*> Result;
	for (auto& WeakNode : StackNodes)
	{
		if (UStackNode* Node = WeakNode.Get())
		{
			Result.Add(Node);
		}
	}
	return Result;
}

UStackViewModel* FStackEditorViewModel::GetViewModelForNode(UStackNode* Node) const
{
	return Node ? Node->GetStackViewModel() : nullptr;
}

void FStackEditorViewModel::SetActiveNode(UStackNode* Node)
{
	ActiveNode = Node;
}

UStackNode* FStackEditorViewModel::GetActiveNode() const
{
	return ActiveNode.Get();
}

void FStackEditorViewModel::SetSelectedEntry(UStackEntry* Entry)
{
	SelectedEntry = Entry;
}

UStackEntry* FStackEditorViewModel::GetSelectedEntry() const
{
	return SelectedEntry.Get();
}

TSharedRef<SWidget> FStackEditorViewModel::CreatePaletteWidget()
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(STextBlock).Text(FText::FromString(TEXT("🧩 Palette (stub)")))
		];
}
