#pragma once
#include "SGraphNode.h"



class UStackNode;
class UStackRoot;
class UStackSelectionViewModel;
class UStackRootViewModel;

class SStackNodeRoot : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SStackNodeRoot) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UStackNode* InNode);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	virtual bool ShouldAllowCulling() const override { return false; }

protected:
	virtual void UpdateGraphNode() override;
	virtual TSharedRef<SWidget> CreateNodeContentArea() override;


	virtual TSharedRef<SWidget> CreateNodeStack();
	TSharedRef<SWidget> CreateTitleWidget(TSharedPtr<SNodeTitle> NodeTitle);

private:
	UStackNode* Node = nullptr;
	UStackRootViewModel* RootViewModel = nullptr;
	UStackSelectionViewModel* SelectionViewModel = nullptr;

	TSharedPtr<SWidget> StackContent;
};
