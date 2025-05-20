#pragma once
#include "CoreMinimal.h"
#include "Graph/UIBuilderGraph.h"
#include "Blueprint/BlueprintExtension.h"
#include "UIBuilderBlueprintExtension.generated.h"



class FUIDesignerBlueprintEditor;

/*
 * Stores per-blueprint state like mode and graph pointer (transient).
 */
UCLASS()
class UIBUILDER_API UUIBuilderBlueprintExtension : public UBlueprintExtension
{
    GENERATED_BODY()

public:

    virtual void PostInitProperties() override;

    FName GetCurrentMode(FUIDesignerBlueprintEditor*) const;
    void SetCurrentMode(FUIDesignerBlueprintEditor* InBlueprintEditor, FName InMode);

    UPROPERTY(Transient)
    TSet<FName> PreviouslyOpenTabs;

    TSharedPtr<FTabManager::FLayout> CapturedGraphLayout;

    int32 DesignerLayoutRestoreCount = 0;
    int32 GraphLayoutRestoreCount = 0;

    FString CapturedGraphLayoutString;
    FString CapturedDesignerLayoutString;

private:

    UPROPERTY(Transient)
    UBlueprint* OwningBlueprint;

    UPROPERTY(Transient)
    FName CurrentMode = "GraphName";

    UFUNCTION()
    void EnsureUIBuilderGraph();

    UPROPERTY()
    UUIBuilderGraph* UIBuilderGraph;

};
