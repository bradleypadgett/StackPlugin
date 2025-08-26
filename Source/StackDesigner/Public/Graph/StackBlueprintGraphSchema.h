#pragma once
#include "CoreMinimal.h"
#include "Editor/StackGraphSchema.h"
#include "BlueprintNodeSpawner.h"
#include "StackBlueprintGraphSchema.generated.h"



/*
 * Defines allowed connections, context menus, and rules for the UI Builder Graph
 */
UCLASS()
class STACKDESIGNER_API UStackBlueprintGraphSchema : public UStackGraphSchema
{
    GENERATED_BODY()

public:

    virtual FText GetGraphCategory(const UEdGraph* Graph) const override;
};
