#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "Blueprint/BlueprintExtension.h"
#include "UIBuilderGraphHolder.h"
#include "UIBuilderBlueprintExtension.generated.h"

UCLASS()
class DETAILSPANELCUSTOMIZATIONEDITOR_API UUIBuilderBlueprintExtension : public UBlueprintExtension
{
    GENERATED_BODY()

public:

    //bool InjectGraphHolderInstance(UBlueprint* BlueprintAsset);

    // The actual graph holder object that stores the UI Builder graph
    UPROPERTY()
    UUIBuilderGraphHolder* GraphHolder = nullptr;
};
