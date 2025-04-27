#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "UIBuilderSubsystem.generated.h"

// Forward declare so we don't need to include here
class UUIBuilderGraph;

USTRUCT(BlueprintType)
struct FPendingButton
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Label;
};

UCLASS()
class DETAILSPANELCUSTOMIZATIONEDITOR_API UUIBuilderSubsystem : public UEditorSubsystem
{
    GENERATED_BODY()

public:

    /** Adds a pending button */
    UFUNCTION(BlueprintCallable, Category = "UIBuilder")
    void AddButton(const FString& Label);

    /** Executes a given UI Builder Graph */
    UFUNCTION(BlueprintCallable, Category = "UIBuilder")
    void ExecuteGraph(UUIBuilderGraph* Graph);

private:

    UPROPERTY()
    TArray<FPendingButton> PendingButtons;
};
