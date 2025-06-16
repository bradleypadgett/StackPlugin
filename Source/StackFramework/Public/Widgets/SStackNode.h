#pragma once
#include "SGraphNode.h"



class UStackNode;
class UStackViewModel;
class UStackSelectionViewModel;

class SStackNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SStackNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UStackNode* InNode);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	virtual bool ShouldAllowCulling() const override { return false; }

protected:
	virtual TSharedRef<SWidget> CreateNodeContentArea() override;

private:
	UStackNode* StackNode = nullptr;
	UStackViewModel* StackViewModel = nullptr;
	UStackSelectionViewModel* SelectionViewModel = nullptr;

	TSharedPtr<SWidget> StackContent;
};
