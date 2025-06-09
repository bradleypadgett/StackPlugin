#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StackEntry.generated.h"



/*
 * Base class for all stack viewmodels and items.
 * Supports nesting, display names, expansion, and refresh behavior.
 */
UCLASS()
class STACKFRAMEWORK_API UStackEntry : public UObject
{
	GENERATED_BODY()

public:
	UStackEntry();

	virtual void RefreshChildren();

	virtual FText GetDisplayName() const;

	virtual bool GetCanExpand() const;

	virtual bool GetShouldShowInStack() const;

	const TArray<UStackEntry*>& GetChildren() const;

protected:
	virtual void RefreshChildrenInternal(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren);

protected:
	UPROPERTY()
	TArray<TObjectPtr<UStackEntry>> Children;
};
