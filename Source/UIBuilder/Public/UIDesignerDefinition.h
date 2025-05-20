
#include "CoreMinimal.h"
#include "AssetDefinition.h"
#include "Script/AssetDefinition_Blueprint.h"
#include "UIDesignerDefinition.generated.h"

UCLASS(meta = (DisplayName = "Blueprint", AssetClass = "/Script/Engine.Blueprint"))
class UIDesignerDefinition : public UAssetDefinition_Blueprint
{
    GENERATED_BODY()

public:

    virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;

    virtual TSoftClassPtr<UObject> GetAssetClass() const override { return UBlueprint::StaticClass(); }

};
