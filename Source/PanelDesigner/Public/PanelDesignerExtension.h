#pragma once
#include "CoreMinimal.h"
#include "Blueprint/BlueprintExtension.h"
#include "PanelDesignerExtension.generated.h"



class FPanelDesignerEditor;
class UPanelDesignerGraph;

/*
 * Transient helper class for serializing graph nodes to the blueprint.
 */
UCLASS(DefaultToInstanced)
class PANELDESIGNER_API UPanelDesignerExtension : public UBlueprintExtension
{
    GENERATED_BODY()

public:

    UPanelDesignerGraph* GetPanelDesignerGraph() const { return PanelDesignerGraph; }

    void AttachPanelDesignerGraph(UBlueprint* Blueprint);

    TObjectPtr<UPanelDesignerGraph> EnsurePanelDesignerGraph();

private:

    //#if WITH_EDITORONLY_DATA
    UPROPERTY()
    TObjectPtr<UPanelDesignerGraph> PanelDesignerGraph;
    //#endif

    UPROPERTY()
    bool bNewExtension = true;
};
