#pragma once

#include "CoreMinimal.h"
#include "Nodes/UIBuilderGraphNode_Base.h"
#include "UIBuilderGraphNode_AddButton.generated.h"

/**
 * Node that represents adding a Button to the UI
 */
UCLASS()
class DETAILSPANELCUSTOMIZATIONEDITOR_API UUIBuilderGraphNode_AddButton : public UUIBuilderGraphNode_Base
{
    GENERATED_BODY()

public:

    // Label for the Button
    UPROPERTY(EditAnywhere, Category = "UI")
    FString ButtonLabel;

    // Constructor
    UUIBuilderGraphNode_AddButton();

    //~ Begin UEdGraphNode Interface
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
    //~ End UEdGraphNode Interface
};
