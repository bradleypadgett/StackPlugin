#pragma once
#include "Blueprint/BlueprintExtension.h"
#include "Definition/StackEditorDataProvider.h"
#include "State/StackDataBase.h"
#include "State/StackEditorData.h"
#include "StackBlueprintExtension.generated.h"



class FStackBlueprintEditor;
class UStackBlueprintGraph;
class UStackEditorData;

/*
 * Transient helper class for serializing graph nodes to the blueprint.
 */
UCLASS(DefaultToInstanced)
class STACKDESIGNER_API UStackBlueprintExtension : public UBlueprintExtension, public IStackEditorDataProvider
{
    GENERATED_BODY()

public:

    TObjectPtr<UStackBlueprintGraph> EnsureStackBlueprintGraph();

    UStackBlueprintGraph* GetStackBlueprintGraph() const { return StackBlueprintGraph; }

    virtual UStackEditorData* GetEditorData() const override { return Cast<UStackEditorData>(StackEditorData); }

private:

    UPROPERTY()
    TObjectPtr<UStackBlueprintGraph> StackBlueprintGraph;

    UPROPERTY()
    TObjectPtr<UStackEditorData> StackEditorData;

    UPROPERTY()
    bool bNewExtension = true;
};