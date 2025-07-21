#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Definition/StackSource.h"
#include "Stack.generated.h"



class UStackRoot;
class UStackEditorData;

/*
 * A reusable stack asset that stores a stack layout (root + child entries).
 * Used for saving and referencing editable stack structures.
 */
UCLASS(BlueprintType)
class STACKFRAMEWORK_API UStack : public UObject, public IStackSource
{
	GENERATED_BODY()

public:
	UStack();

	UPROPERTY(EditAnywhere, Instanced, Category="Stack")
	UStackRoot* RootEntry;

	UPROPERTY(EditAnywhere, Category="Metadata")
	FGuid StackID = FGuid::NewGuid();

	UPROPERTY(EditAnywhere, Category="Metadata")
	FName StackCategory;

	const FString& GetUniqueName();
	bool SetUniqueName(const FString& InName);

public:
	// IStackSource implementation
	virtual UStack& GetStack() override { return *this; }
	virtual const UStack& GetStack() const override { return *this; }
	virtual UStackEditorData* GetStackEditorData() const override;

	UPROPERTY()
	TObjectPtr<UStackEditorData> StackEditorData;

private:
	UPROPERTY()
	FString UniqueName;
};
