#pragma once
#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "BlueprintNodeSpawner.h"
#include "UIBuilderGraphSchema.generated.h"



/**
 * Defines allowed connections, context menus, and rules for the UI Builder Graph
 */
UCLASS()
class DETAILSPANELCUSTOMIZATIONEDITOR_API UUIBuilderGraphSchema : public UEdGraphSchema
{
    GENERATED_BODY()

public:

    virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
 
    // Custom Action to spawn nodes inside the UI Builder Graph
    struct FToolUI_NewNodeAction : public FEdGraphSchemaAction
    {
        UBlueprintNodeSpawner* NodeSpawner;

        FToolUI_NewNodeAction(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, int32 InGrouping)
            : FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping)
        {
            NodeSpawner = nullptr;
        }
        virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode) override;
    };

    virtual FText GetGraphCategory(const UEdGraph* Graph) const override;
};
