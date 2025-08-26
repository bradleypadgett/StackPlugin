#include "ViewModels/Editor/StackSystemGraphManager.h"
#include "ViewModels/Editor/StackSystemManager.h"
#include "EditorData/StackSystemEditorData.h"
#include "Utilities/StackGraphUtilities.h"
#include "ViewModels/StackEntry.h"
#include "Editor/StackGraph.h"
//#include "StackObjectSelection.h"



FStackSystemGraphManager::FStackSystemGraphManager()
{
	//NodeSelection = MakeShared<FStackObjectSelection>();
}

FStackSystemGraphManager::~FStackSystemGraphManager()
{

}

void FStackSystemGraphManager::Initialize(TSharedRef<FStackSystemManager> InSystemManager)
{
	SystemManager = InSystemManager;
	SystemGraph = InSystemManager->GetSystemEditorData().GetSystemGraph();

	if (UStackGraph* TypedGraph = Cast<UStackGraph>(SystemGraph))
	{
		TypedGraph->Initialize(SystemManager.Pin());
	}

	// TO-DO ~ selection delegate hookup

	UpdateSystemGraphNodes();
}

TSharedRef<FStackSystemManager> FStackSystemGraphManager::GetSystemManager() const
{
	return SystemManager.Pin().ToSharedRef();
}

UEdGraph* FStackSystemGraphManager::GetGraph() const
{
	return SystemGraph.Get();
}
/*
TSharedRef<FStackObjectSelection> FStackSystemGraphManager::GetNodeSelection() const
{
	return NodeSelection.ToSharedRef();
}
*/
void FStackSystemGraphManager::UpdateSystemGraphNodes()
{
	CachedStackEntries.Reset();

	if (UEdGraph* CurrentGraph = SystemGraph.Get())
	{
		TArray<UStackEntry*> Entries = FStackGraphUtilities::GetAllStackEntries(CurrentGraph);
		for (UStackEntry* Entry : Entries)
		{
			CachedStackEntries.Add(Entry);
		}
	}
}

void FStackSystemGraphManager::PostUndo(bool bSuccess)
{
	UpdateSystemGraphNodes();
}
