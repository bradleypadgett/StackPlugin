#include "UIBuilderSubsystem.h"
#include "Graph/UIBuilderGraph.h"
#include "Nodes/UIBuilderGraphNode_AddButton.h"

void UUIBuilderSubsystem::AddButton(const FString& Label)
{
	UE_LOG(LogTemp, Warning, TEXT("Button Added: %s"), *Label);
	PendingButtons.Add(FPendingButton{ Label });
}

void UUIBuilderSubsystem::ExecuteGraph(UUIBuilderGraph* Graph)
{
    if (!Graph)
    {
        UE_LOG(LogTemp, Warning, TEXT("ExecuteGraph: No Graph provided!"));
        return;
    }

    for (UEdGraphNode* Node : Graph->Nodes)
    {
        if (!Node || !Node->IsA<UUIBuilderGraphNode_AddButton>())
        {
            continue;
        }

        UUIBuilderGraphNode_AddButton* ButtonNode = Cast<UUIBuilderGraphNode_AddButton>(Node);

        if (ButtonNode)
        {
            // THIS is where you finally call your Subsystem's AddButton!
            AddButton(ButtonNode->ButtonLabel);

            UE_LOG(LogTemp, Warning, TEXT("Built Button from Graph: %s"), *ButtonNode->ButtonLabel);
        }
    }
}