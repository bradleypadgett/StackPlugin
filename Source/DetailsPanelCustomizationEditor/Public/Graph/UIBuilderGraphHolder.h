#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UIBuilderGraphHolder.generated.h"

class UUIBuilderGraph;

/**
 * Lightweight holder that stores a Tool UI Graph inside an Actor
 */
UCLASS(BlueprintType)
class DETAILSPANELCUSTOMIZATIONEDITOR_API UUIBuilderGraphHolder : public UObject
{
    GENERATED_BODY()

public:

    /** The Tool UI Graph assigned to this Actor */
    UPROPERTY(EditAnywhere, Instanced, Category="UIBuilder")
    UUIBuilderGraph* UIBuilderGraph;
};
