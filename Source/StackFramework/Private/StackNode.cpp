#include "StackNode.h"
#include "ViewModels/Editor/StackViewModel.h"



#define LOCTEXT_NAMESPACE "StackNode"

UStackNode::UStackNode()
{

}

void UStackNode::Initialize(UObject* InOwnerContext)
{
	OwnerContext = InOwnerContext; // UObject for flexibility. Might change dunno yet
	StackViewModel = NewObject<UStackViewModel>(this);
	StackViewModel->Initialize(this, true);
}

UStackViewModel* UStackNode::GetStackViewModel() const
{
	return StackViewModel;
}

FText UStackNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("StackNodeTitle", "Stack Node");
}

FLinearColor UStackNode::GetNodeTitleColor() const
{
	return FLinearColor(0.013575f, 0.770000f, 0.429609f); // soft green
}

#undef LOCTEXT_NAMESPACE
