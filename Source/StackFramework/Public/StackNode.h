#pragma once
#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "StackNode.generated.h"



class UStackViewModel;

/*
 * EdGraph node representing a stack graph entry (e.g., one tab or section).
 */
UCLASS()
class STACKFRAMEWORK_API UStackNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UStackNode();

	void Initialize(UObject* InOwnerContext);

	UStackViewModel* GetStackViewModel() const;

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual bool CanDuplicateNode() const override { return true; }

private:
	UPROPERTY()
	TObjectPtr<UObject> OwnerContext;

	UPROPERTY()
	TObjectPtr<UStackViewModel> StackViewModel;
};
