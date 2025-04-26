#include "ToolBaseActor.h"

AToolBaseActor::AToolBaseActor()
{
    PrimaryActorTick.bCanEverTick = false;
}

/*
bool AToolBaseActor::CanEditPropertyByName_Implementation(FName PropertyName) const
{
    UE_LOG(LogTemp, Warning, TEXT("CanEditPropertyByName_Implementation fired!"));
    return true; // Blueprint can override this!
}
*/

bool AToolBaseActor::CanEditChange(const FProperty* InProperty) const
{
    
    if (HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
    {
        UE_LOG(LogTemp, Warning, TEXT("Object is a template/archetype — cannot edit."));
        return false;
    }

    const FName PropName = InProperty ? InProperty->GetFName() : NAME_None;
    bool bisEditable = CanEditPropertyByName(PropName);
    UE_LOG(LogTemp, Warning, TEXT("Class: %s"), *GetClass()->GetName());

    UE_LOG(LogTemp, Warning, TEXT("CanEditChange: %s -> %s"), *PropName.ToString(), bEditable ? TEXT("TRUE") : TEXT("FALSE"));
        
    return bisEditable;
}
