#include "Nodes/ToolUIGraphNode_AddButton.h"

#define LOCTEXT_NAMESPACE "ToolUIGraphNode_AddButton"

UToolUIGraphNode_AddButton::UToolUIGraphNode_AddButton()
{
    ButtonLabel = TEXT("New Button");
}

FText UToolUIGraphNode_AddButton::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    return FText::FromString(FString::Printf(TEXT("Add Button: %s"), *ButtonLabel));
}

#undef LOCTEXT_NAMESPACE
