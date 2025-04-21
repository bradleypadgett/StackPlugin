#include "FCustomizeToolActorDetails.h"
#include "DetailLayoutBuilder.h"
#include "PropertyHandle.h"


void FCustomizeToolActorDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
    UE_LOG(LogTemp, Warning, TEXT("CustomizeDetails active!"));

    /* 1. Get whichever object(s) the Details panel is showing */
    TArray<TWeakObjectPtr<UObject>> CustomizedObjects;
    DetailBuilder.GetObjectsBeingCustomized(CustomizedObjects);

    if (CustomizedObjects.Num() == 0 || !CustomizedObjects[0].IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("No valid objects being customized."));
        return;
    }

    UObject* Target = CustomizedObjects[0].Get();
    UClass* TargetClass = Target->GetClass();

    /* 2. Reflect over every FProperty on that class */
    for (TFieldIterator<FProperty> PropIt(TargetClass); PropIt; ++PropIt)
    {
        const FProperty* Prop = *PropIt;
        if (Prop)
        {
            UE_LOG(LogTemp, Warning, TEXT("  • Property: %s"), *Prop->GetName());
        }
    }
}

TSharedRef<IDetailCustomization> FCustomizeToolActorDetails::MakeInstance()
{
    return MakeShared<FCustomizeToolActorDetails>();
}

