#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToolBaseActor.generated.h"

UCLASS()
class DETAILSPANELCUSTOMIZATIONRUNTIME_API AToolBaseActor : public AActor
{
    GENERATED_BODY()


public:

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Tool")
    bool CanEditPropertyByName(FName PropertyName) const;

    virtual bool CanEditProperty(const FProperty* InProperty) const;

    AToolBaseActor();
};
