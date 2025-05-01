#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UIBuilderGraphHolder.generated.h"



class UUIBuilderGraph;

/**
 * Lightweight holder that stores a UIBuilderGraph inside an Actor
 */
UCLASS(BlueprintType)
class DETAILSPANELCUSTOMIZATIONEDITOR_API UUIBuilderGraphHolder : public UObject
{
    GENERATED_BODY()

public:

    //The UIBuilderGraph assigned to this Actor
    UPROPERTY(EditAnywhere, Instanced, Category="UIBuilder")
    UUIBuilderGraph* UIBuilderGraph;

    // UObject override to auto-create Graph when needed
    virtual void PostInitProperties() override;

};
