#pragma once
#include "AssetDefinition.h"
#include "Script/AssetDefinition_Blueprint.h"
#include "StackBlueprintDefinition.generated.h"



/*
*  Intercepts blueprints' opening behavior for overriding AActor blueprints to use StackBlueprint's editor
*/
UCLASS(meta = (DisplayName = "Blueprint", AssetClass = "/Script/Engine.Blueprint"))
class UStackBlueprintDefinition : public UAssetDefinition_Blueprint
{
    GENERATED_BODY()

public:

    virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;
    virtual TSoftClassPtr<UObject> GetAssetClass() const override { return UBlueprint::StaticClass(); }
};
