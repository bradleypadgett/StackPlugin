#include "Editor/StackGraphSchema.h"
#include "EdGraph/EdGraphSchema.h"
#include "Editor/StackNodeSchemaAction.h"
#include "Editor/StackNode.h"
#include "ToolMenuSection.h"
#include "Providers/StackSource.h"
#include "Editor/StackGraph.h"
#include "ViewModels/Editor/StackSystemManager.h"



#define LOCTEXT_NAMESPACE "StackGraphSchema"

void UStackGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	if (const UStackGraph* StackGraph = Cast<UStackGraph>(ContextMenuBuilder.CurrentGraph))
	{
		if (TSharedPtr<FStackSystemManager> Manager = StackGraph->SystemManagerWeak.Pin())
		{
			TSharedPtr<FStackNodeSchemaAction> Action = MakeShared<FStackNodeSchemaAction>(Manager);
			ContextMenuBuilder.AddAction(Action);
		}
	}

}



#undef LOCTEXT_NAMESPACE
