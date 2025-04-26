#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "KismetCompiler.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "K2Node_AddButton.generated.h"


UCLASS()
class DETAILSPANELCUSTOMIZATIONEDITOR_API UK2Node_AddButton : public UK2Node
{
    GENERATED_BODY()

public:
    // How the node behaves
    virtual void AllocateDefaultPins() override;
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
    virtual FText GetTooltipText() const override;
    virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
    virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
    virtual FText GetMenuCategory() const override;
};
