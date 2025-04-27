#pragma once

#include "CoreMinimal.h"
#include "Nodes/ToolUIGraphNode_Base.h"
#include "ToolUIGraphNode_AddButton.generated.h"

/**
 * Node that represents adding a Button to the UI
 */
UCLASS()
class DETAILSPANELCUSTOMIZATIONEDITOR_API UToolUIGraphNode_AddButton : public UToolUIGraphNode_Base
{
    GENERATED_BODY()

public:

    // Label for the Button
    UPROPERTY(EditAnywhere, Category = "UI")
    FString ButtonLabel;

    // Constructor
    UToolUIGraphNode_AddButton();

    //~ Begin UEdGraphNode Interface
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
    //~ End UEdGraphNode Interface
};
