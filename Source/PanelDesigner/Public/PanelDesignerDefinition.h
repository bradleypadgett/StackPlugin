
#include "CoreMinimal.h"
#include "AssetDefinition.h"
#include "Script/AssetDefinition_Blueprint.h"
#include "PanelDesignerDefinition.generated.h"



/*
*  Intercepts blueprints' opening behavior for overriding AActor blueprints to use PanelDesigner's editor
*/
UCLASS(meta = (DisplayName = "Blueprint", AssetClass = "/Script/Engine.Blueprint"))
class UPanelDesignerDefinition : public UAssetDefinition_Blueprint
{
    GENERATED_BODY()

public:

    virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;
    virtual TSoftClassPtr<UObject> GetAssetClass() const override { return UBlueprint::StaticClass(); }
};
