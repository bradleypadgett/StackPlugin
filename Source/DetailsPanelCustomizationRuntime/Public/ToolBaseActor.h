#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/Field.h"
#include "ToolBaseActor.generated.h"

UCLASS()
class DETAILSPANELCUSTOMIZATIONRUNTIME_API AToolBaseActor : public AActor
{
    GENERATED_BODY()


public:

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Tool")
    bool CanEditPropertyByName(FName PropertyName) const;



    virtual bool CanEditChange(const FProperty* InProperty) const override;

    AToolBaseActor();
};