#pragma once
#include "Blueprint/BlueprintExtension.h"
#include "Definition/StackSource.h"
#include "State/StackEditorState.h"
#include "Stack.h"
#include "StackBlueprintExtension.generated.h"



class FStackBlueprintEditor;
class UStackBlueprintGraph;
class UStackEditorState;

/*
 * Transient helper class for serializing graph nodes to the blueprint.
 */
UCLASS(DefaultToInstanced)
class STACKDESIGNER_API UStackBlueprintExtension : public UBlueprintExtension, public IStackSource
{
    GENERATED_BODY()

public:

    TObjectPtr<UStackBlueprintGraph> EnsureStackBlueprintGraph();

    UStackBlueprintGraph* GetStackBlueprintGraph() const { return StackBlueprintGraph; }


public:

    virtual UStack& GetStack() override { return *Stack; };
    virtual const UStack& GetStack() const override { return *Stack; };
    virtual UStackEditorState* GetStackEditorState() const override { return Cast<UStackEditorState>(StackEditorState); }

private:

    UPROPERTY()
    TObjectPtr<UStackBlueprintGraph> StackBlueprintGraph;

    UPROPERTY()
    TObjectPtr<UStackEditorState> StackEditorState;

    UPROPERTY()
    TObjectPtr<UStack> Stack;

    UPROPERTY()
    bool bNewExtension = true;
};