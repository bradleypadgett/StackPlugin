#include "StackBlueprintExtension.h"
#include "Graph/StackBlueprintGraphSchema.h"
#include "Graph/StackBlueprintGraph.h"
#include "EdGraph/EdGraph.h"
#include "StackSystem.h"
#include "ViewModels/Editor/StackSystemManager.h"
#include "EditorData/StackSystemEditorData.h"



void UStackBlueprintExtension::Initialize()
{
    InitializeStackSystem();
	//EnsureStackBlueprintGraph();
}

// Creates and serializes StackBlueprintGraph into owning blueprint if it doesn't have one
void UStackBlueprintExtension::EnsureStackBlueprintGraph()
{
	if (!StackSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("No StackSystem set — cannot retrieve system graph."));
		return;
	}

	if (UStackSystemEditorData* EditorData = StackSystem->GetSystemEditorData())
	{
		if (UEdGraph* SystemGraph = EditorData->GetSystemGraph())
		{
			UE_LOG(LogTemp, Log, TEXT("Found existing SystemGraph in StackSystemEditorData."));
			return;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Could not find or create SystemGraph."));
}


// TO-DO ~ Make temporary vs permanent function variants (temp system or input system asset). *Also, move into interface IStackSystemProvider
void UStackBlueprintExtension::InitializeStackSystem()
{
    if (!StackSystem) 
        StackSystem = NewObject<UStackSystem>(this, UStackSystem::StaticClass(), NAME_None, RF_Transactional);

    // TO-DO ~ System Options initialization
    // - 'bUseSystemGraph' = true (Uses graph from StackSystemEditorData to render Stacks. false is for custom Stack node injection)

    StackSystemManager = MakeShared<FStackSystemManager>();
    StackSystemManager->Initialize(*StackSystem, false);

    // TO-DO ~ Initialize parameters panel. Also separate into isolated function

    // TO-DO ~ Add bindings for SystemManager->Editor stuff. Not sure how to integrate w/ interface yet.
}