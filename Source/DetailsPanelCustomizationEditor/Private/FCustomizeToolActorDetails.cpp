#include "FCustomizeToolActorDetails.h"
#include "DetailLayoutBuilder.h"
//#include "ToolBaseActor.h"
#include "PropertyHandle.h"

/*
void FCustomizeToolActorDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{

    UE_LOG(LogTemp, Warning, TEXT("CustomizeDetails active!"));

    // Get customized objects
    TArray<TWeakObjectPtr<UObject>> CustomizedObjects;
    DetailBuilder.GetObjectsBeingCustomized(CustomizedObjects);

    UE_LOG(LogTemp, Warning, TEXT("CustomizeObject ?"));
    if (CustomizedObjects.Num() == 0 || !CustomizedObjects[0].IsValid()) return;
    UE_LOG(LogTemp, Warning, TEXT("CustomizeObject!!!"));

    UE_LOG(LogTemp, Warning, TEXT("ToolActor ?"));
    // Try to cast to ToolBaseActor
    AToolBaseActor* ToolActor = Cast<AToolBaseActor>(CustomizedObjects[0].Get());
    if (!ToolActor) return;
    UE_LOG(LogTemp, Warning, TEXT("ToolActor!!!"));

    // Example call to CanEditPropertyByName
    const bool bCanEditTest = ToolActor->CanEditPropertyByName(FName("TestProperty"));
    UE_LOG(LogTemp, Warning, TEXT("CanEdit TestProperty: %s"), bCanEditTest ? TEXT("TRUE") : TEXT("FALSE"));
}

TSharedRef<IDetailCustomization> FCustomizeToolActorDetails::MakeInstance()
{
    return MakeShared<FCustomizeToolActorDetails>();
}
*/