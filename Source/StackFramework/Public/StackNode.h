#pragma once
#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "StackNode.generated.h"



class UStackSystem;
class FStackHandleViewModel;

UCLASS(MinimalAPI)
class UStackNode : public UEdGraphNode
{
	GENERATED_BODY()
public:
	UStackNode();

	void Initialize(UStackSystem* InOwningSystem);
	void UpdateState() {};
	const FGuid GetHandleID() const;
	struct FStackHandle* TryGetHandle() const;

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;

	virtual bool CanUserDeleteNode() const override;
	virtual bool CanDuplicateNode() const override;

	virtual void OnRenameNode(const FString& NewName) override;
	virtual bool GetCanRenameNode() const override;

	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;
	virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const override;


	UStackSystem* GetOwningSystem() const;

	void SetIsRenameQueued(bool InQueueState) { bIsRenameQueued = InQueueState; }
	bool GetIsRenameQueued() const { return bIsRenameQueued; }

private:
	UPROPERTY()
	TObjectPtr<UStackSystem> OwningSystem;

	UPROPERTY()
	FGuid HandleID;

	bool bIsRenameQueued;
};
