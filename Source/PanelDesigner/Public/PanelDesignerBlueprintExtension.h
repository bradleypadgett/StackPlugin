#pragma once
#include "CoreMinimal.h"
#include "Graph/PanelDesignerGraph.h"
#include "Blueprint/BlueprintExtension.h"
#include "PanelDesignerBlueprintExtension.generated.h"



class FPanelDesignerBlueprintEditor;

/*
 * Transient helper class for serializing graph nodes to the blueprint.
 */
UCLASS()
class PANELDESIGNER_API UPanelDesignerBlueprintExtension : public UBlueprintExtension
{
    GENERATED_BODY()

public:

    virtual void PostInitProperties() override;
    UPanelDesignerGraph* EnsurePanelDesignerGraph();

private:

    UPROPERTY(Transient)
    UBlueprint* OwningBlueprint;

    UPROPERTY()
    UPanelDesignerGraph* PanelDesignerGraph;
};
