#include "ViewModels/Editor/StackViewModel.h"
#include "Definition/StackSource.h"
#include "State/StackEditorState.h"
#include "Stack.h"
#include "State/StackViewState.h"
#include "ViewModels/Editor/StackHandleViewModel.h"



FStackViewModel::FStackViewModel()
{

}

FStackViewModel::~FStackViewModel()
{

}

void FStackViewModel::Initialize(TScriptInterface<IStackSource> InStackSource)
{
	StackSource = InStackSource;
}

UStackEditorState* FStackViewModel::GetStackEditorState() const
{
	return StackSource->GetStackEditorState();
}

UStackViewState& FStackViewModel::GetStackViewState() const
{
	return StackSource->GetStackEditorState()->GetStackViewState();
}

IStackSource* FStackViewModel::GetStackSource() const
{
	return StackSource.GetInterface();
}


TSharedPtr<FStackHandleViewModel> FStackViewModel::GetHandleViewModel(const FStackHandleViewModel& InHandleViewModel) const
{
	return HandleViewModel;
}
