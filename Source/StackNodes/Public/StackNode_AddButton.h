#pragma once
#include "CoreMinimal.h"
#include "StackNode_Base.h"
#include "StackNode_AddButton.generated.h"



/*
 * Node that represents adding a Button to the UI
 */
UCLASS()
class STACKNODES_API UStackNode_AddButton : public UStackNode_Base
{
    GENERATED_BODY()

public:

    UStackNode_AddButton();

    // Label for the Button
    UPROPERTY(EditAnywhere, Category = "UI")
    FString ButtonLabel;

    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};
