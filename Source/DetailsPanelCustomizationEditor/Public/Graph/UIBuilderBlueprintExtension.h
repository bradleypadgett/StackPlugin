#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "Blueprint/BlueprintExtension.h"
#include "UIBuilderGraph.h"
#include "UIBuilderBlueprintExtension.generated.h"

UCLASS()
class DETAILSPANELCUSTOMIZATIONEDITOR_API UUIBuilderBlueprintExtension : public UBlueprintExtension
{
    GENERATED_BODY()

public:

    UPROPERTY()
    UUIBuilderGraph* UIBuilderGraph = nullptr;
};
