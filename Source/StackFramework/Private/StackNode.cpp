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
	// Maybe initialize stack viewmodel
}

UStackViewModel* UStackNode::GetStackViewModel() const
{
	return StackViewModel;
}

FText UStackNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("StackNodeTitle", "Stack Node");
}

#undef LOCTEXT_NAMESPACE
