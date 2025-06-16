#include "Graph/StackGraphSchema.h"
#include "EdGraph/EdGraphSchema.h"
#include "Graph/StackGraphUtilities.h"
#include "Graph/StackNodeSchemaAction.h"
#include "StackNode.h"
#include "ToolMenuSection.h"



#define LOCTEXT_NAMESPACE "StackGraphSchema"

void UStackGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	ContextMenuBuilder.AddAction(MakeShared<FStackNodeSchemaAction>());
}


#undef LOCTEXT_NAMESPACE
