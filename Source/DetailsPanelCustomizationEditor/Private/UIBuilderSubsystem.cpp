// UUIBuilderSubsystem.cpp
#include "UIBuilderSubsystem.h"

void UUIBuilderSubsystem::AddButton(const FString& Label)
{
	UE_LOG(LogTemp, Warning, TEXT("Button Added: %s"), *Label);
	PendingButtons.Add(FPendingButton{ Label });
}
