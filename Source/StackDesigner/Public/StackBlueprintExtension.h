#pragma once
#include "Blueprint/BlueprintExtension.h"
#include "Providers/Editor/StackSystemProvider.h"
#include "EditorData/StackEditorData.h"
#include "Stack.h"
#include "StackSystem.h" // TO-DO ~ (can remove after fixing GetStackBlueprintGraph's comment)
#include "EditorData/StackSystemEditorData.h" // ^^ Ditto. not the pokemon
#include "StackBlueprintExtension.generated.h"



class FStackBlueprintEditor;
class UStackBlueprintGraph;
class UStackEditorData;
class UStackSystem;
class FStackSystemManager;

/*
 * Transient helper class for serializing graph nodes to the blueprint.
 */
UCLASS(DefaultToInstanced)
class STACKDESIGNER_API UStackBlueprintExtension : public UBlueprintExtension, public IStackSystemProvider
{
    GENERATED_BODY()

public:

    void Initialize();

    void EnsureStackBlueprintGraph();
    void InitializeStackSystem();

    // TO-DO ~ this is an important refactor!! fully transition to using the SystemEditorData. this is a 'lil patch while transitioning to that.
    UEdGraph* GetStackBlueprintGraph() const {
        UE_LOG(LogTemp, Warning, TEXT("grabbing SystemGraph!"));
        return StackSystem->GetSystemEditorData()->GetSystemGraph(); }


public:

    virtual UStackSystem* GetStackSystem() const override { return StackSystem; };
    virtual TSharedPtr<FStackSystemManager> GetStackSystemManager() const override { return StackSystemManager; };


private:
    UPROPERTY()
    UStackSystem* StackSystem;

    TSharedPtr<FStackSystemManager> StackSystemManager;

    UPROPERTY()
    TObjectPtr<UStackBlueprintGraph> StackBlueprintGraph;

    UPROPERTY()
    bool bNewExtension = true;
};