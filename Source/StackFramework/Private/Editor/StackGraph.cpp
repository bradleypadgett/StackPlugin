#include "Editor/StackGraph.h"
#include "Editor/StackGraphSchema.h"
#include "ViewModels/Editor/StackSystemManager.h"



UStackGraph::UStackGraph()
{
}

void UStackGraph::Initialize(TSharedPtr<FStackSystemManager> InSystemManager)
{
	SystemManagerWeak = InSystemManager;
}
