// UUIBuilderSubsystem.h
#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "UIBuilderSubsystem.generated.h"

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
    UFUNCTION(BlueprintCallable, Category="UIBuilder")
    void AddButton(const FString& Label);

private:
    UPROPERTY()
    TArray<FPendingButton> PendingButtons;
};
