#include "Nodes/UIBuilderGraphNode_AddButton.h"

#define LOCTEXT_NAMESPACE "UIBuilderGraphNode_AddButton"

UUIBuilderGraphNode_AddButton::UUIBuilderGraphNode_AddButton()
{
    ButtonLabel = TEXT("New Button");
}

FText UUIBuilderGraphNode_AddButton::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    return FText::FromString(FString::Printf(TEXT("Add Button: %s"), *ButtonLabel));
}

#undef LOCTEXT_NAMESPACE
