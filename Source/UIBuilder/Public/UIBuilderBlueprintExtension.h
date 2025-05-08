#pragma once
#include "CoreMinimal.h"
#include "Blueprint/BlueprintExtension.h"
#include "Graph/UIBuilderGraph.h"
#include "UIBuilderBlueprintExtension.generated.h"



DECLARE_MULTICAST_DELEGATE_OneParam(FOnUIBuilderModeChanged, FName);

/*
 * Stores per-blueprint state like mode and graph pointer (transient).
 */
UCLASS()
class UIBUILDER_API UUIBuilderBlueprintExtension : public UBlueprintExtension
{
    GENERATED_BODY()

public:

    virtual void PostInitProperties() override;

    FName GetCurrentMode() const { return CurrentMode; }
    void SetCurrentMode(FName InMode);

    FOnUIBuilderModeChanged& OnModeChanged() { return ModeChangedDelegate; }

private:

    UFUNCTION()
    void EnsureUIBuilderGraph();

    UPROPERTY(Transient)
    UBlueprint* OwningBlueprint;

    UPROPERTY(Transient)
    UUIBuilderGraph* UIBuilderGraph;

    UPROPERTY(Transient)
    FName CurrentMode = "Graph";

    FOnUIBuilderModeChanged ModeChangedDelegate;

};
