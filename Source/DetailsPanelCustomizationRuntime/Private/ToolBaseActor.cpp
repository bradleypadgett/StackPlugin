#include "ToolBaseActor.h"

AToolBaseActor::AToolBaseActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

bool AToolBaseActor::CanEditProperty(const FProperty* InProperty) const
{
    const FName PropName = InProperty->GetFName();

    UE_LOG(LogTemp, Warning, TEXT("C++ CanEditProperty: %s"), *PropName.ToString());

    return CanEditPropertyByName(PropName);
}


bool AToolBaseActor::CanEditPropertyByName_Implementation(FName PropertyName) const
{
    // Default to editable unless Blueprint says otherwise
    return true;
}
