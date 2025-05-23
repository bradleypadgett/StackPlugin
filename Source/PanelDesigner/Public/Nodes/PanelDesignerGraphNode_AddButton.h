#pragma once
#include "CoreMinimal.h"
#include "Nodes/PanelDesignerGraphNode_Base.h"
#include "PanelDesignerGraphNode_AddButton.generated.h"



/*
 * Node that represents adding a Button to the UI
 */
UCLASS()
class PANELDESIGNER_API UPanelDesignerGraphNode_AddButton : public UPanelDesignerGraphNode_Base
{
    GENERATED_BODY()

public:

    UPanelDesignerGraphNode_AddButton();

    // Label for the Button
    UPROPERTY(EditAnywhere, Category = "UI")
    FString ButtonLabel;

    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
};
