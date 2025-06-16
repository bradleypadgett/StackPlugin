#include "ViewModels/Editor/StackGraphViewModel.h"
#include "ViewModels/Editor/StackEditorViewModel.h"
#include "Graph/StackGraphUtilities.h"
#include "ViewModels/StackEntry.h"
//#include "StackObjectSelection.h"



FStackGraphViewModel::FStackGraphViewModel()
{
	//NodeSelection = MakeShared<FStackObjectSelection>();
}

FStackGraphViewModel::~FStackGraphViewModel()
{

}

void FStackGraphViewModel::Initialize(TSharedRef<FStackEditorViewModel> InEditorViewModel, UEdGraph* InGraph)
{
	EditorViewModel = InEditorViewModel;
	Graph = InGraph;
}

TSharedRef<FStackEditorViewModel> FStackGraphViewModel::GetEditorViewModel() const
{
	return EditorViewModel.Pin().ToSharedRef();
}

UEdGraph* FStackGraphViewModel::GetGraph() const
{
	return Graph.Get();
}
/*
TSharedRef<FStackObjectSelection> FStackGraphViewModel::GetNodeSelection() const
{
	return NodeSelection.ToSharedRef();
}
*/
void FStackGraphViewModel::UpdateGraphNodes()
{
	CachedStackEntries.Reset();

	if (UEdGraph* CurrentGraph = Graph.Get())
	{
		TArray<UStackEntry*> Entries = FStackGraphUtilities::GetAllStackEntries(CurrentGraph);
		for (UStackEntry* Entry : Entries)
		{
			CachedStackEntries.Add(Entry);
		}
	}
}

void FStackGraphViewModel::PostUndo(bool bSuccess)
{
	UpdateGraphNodes();
}
