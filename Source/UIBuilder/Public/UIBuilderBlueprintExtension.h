#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "Blueprint/BlueprintExtension.h"
#include "Graph/UIBuilderGraph.h"
#include "UIBuilderBlueprintExtension.generated.h"

UCLASS()
class UIBUILDER_API UUIBuilderBlueprintExtension : public UBlueprintExtension
{
    GENERATED_BODY()

public:

    UPROPERTY()
    UUIBuilderGraph* UIBuilderGraph = nullptr;
};
