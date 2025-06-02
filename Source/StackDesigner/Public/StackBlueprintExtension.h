#pragma once
#include "Blueprint/BlueprintExtension.h"
#include "StackBlueprintExtension.generated.h"



class FStackBlueprintEditor;
class UStackBlueprintGraph;

/*
 * Transient helper class for serializing graph nodes to the blueprint.
 */
UCLASS(DefaultToInstanced)
class STACKDESIGNER_API UStackBlueprintExtension : public UBlueprintExtension
{
    GENERATED_BODY()

public:

    TObjectPtr<UStackBlueprintGraph> EnsureStackBlueprintGraph();

    UStackBlueprintGraph* GetStackBlueprintGraph() const { return StackBlueprintGraph; }

private:

    UPROPERTY()
    TObjectPtr<UStackBlueprintGraph> StackBlueprintGraph;

    UPROPERTY()
    bool bNewExtension = true;
};