#include "StackNode_AddButton.h"



// Might add in later if I wanna support other languages. Just so I don't forget 🤗💕
//#define LOCTEXT_NAMESPACE "StackNode_AddButton"

UStackNode_AddButton::UStackNode_AddButton()
{
    ButtonLabel = TEXT("New Button");
}

FText UStackNode_AddButton::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    return FText::FromString(FString::Printf(TEXT("Add Button: %s"), *ButtonLabel));
}

//#undef LOCTEXT_NAMESPACE
