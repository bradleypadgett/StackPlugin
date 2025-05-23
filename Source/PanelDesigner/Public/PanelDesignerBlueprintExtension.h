#pragma once
#include "CoreMinimal.h"
#include "Graph/PanelDesignerGraph.h"
#include "Blueprint/BlueprintExtension.h"
#include "PanelDesignerBlueprintExtension.generated.h"



class FPanelDesignerBlueprintEditor;

/*
 * Stores per-blueprint state like mode and graph pointer (transient).
 */
UCLASS()
class PANELDESIGNER_API UPanelDesignerBlueprintExtension : public UBlueprintExtension
{
    GENERATED_BODY()

public:

    virtual void PostInitProperties() override;

    UPROPERTY(Transient)
    TSet<FName> PreviouslyOpenTabs;

    TSharedPtr<FTabManager::FLayout> CapturedGraphLayout;

    int32 DesignerLayoutRestoreCount = 0;
    int32 GraphLayoutRestoreCount = 0;

    FString CapturedGraphLayoutString;
    FString CapturedDesignerLayoutString;

    UPanelDesignerGraph* EnsurePanelDesignerGraph();

private:

    UPROPERTY(Transient)
    UBlueprint* OwningBlueprint;

    UPROPERTY(Transient)
    FName CurrentMode = "GraphName";

    UPROPERTY()
    UPanelDesignerGraph* PanelDesignerGraph;

};
