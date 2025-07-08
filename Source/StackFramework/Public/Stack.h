#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Stack.generated.h"



class UStackRoot;
class FStackData;

/*
 * A reusable stack asset that stores a stack layout (root + child entries).
 * Used for saving and referencing editable stack structures.
 */
UCLASS(BlueprintType)
class STACKFRAMEWORK_API UStack : public UObject
{
	GENERATED_BODY()

public:
	UStack();

	UPROPERTY(EditAnywhere, Instanced, Category="Stack")
	UStackRoot* RootEntry;

	UPROPERTY(EditAnywhere, Category="Metadata")
	FGuid StackID = FGuid::NewGuid();

	// Categorization for organizing stacks.
	UPROPERTY(EditAnywhere, Category="Metadata")
	FName StackCategory;

	const FString& GetUniqueName();
	bool SetUniqueName(const FString& InName);

	FStackData* GetStackData(const FGuid& InStackID);

private:
	UPROPERTY()
	FString UniqueName;
};
