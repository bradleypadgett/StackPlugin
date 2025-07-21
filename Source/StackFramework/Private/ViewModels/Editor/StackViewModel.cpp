#include "ViewModels/Editor/StackViewModel.h"
#include "Definition/StackSource.h"
#include "EditorData/StackEditorData.h"
#include "Stack.h"
#include "EditorData/StackEntryEditorData.h"
#include "ViewModels/Editor/StackHandleViewModel.h"
#include "ViewModels/Editor/StackScriptViewModel.h"



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

UStackEditorData& FStackViewModel::GetStackEditorData() const
{
	return *StackSource->GetStackEditorData();
}

IStackSource* FStackViewModel::GetStackSource() const
{
	return StackSource.GetInterface();
}


TSharedPtr<FStackHandleViewModel> FStackViewModel::GetHandleViewModel(const FStackHandleViewModel& InHandleViewModel) const
{
	return HandleViewModel;
}

TSharedRef<FStackScriptViewModel> FStackViewModel::GetScriptViewModel()
{
	return ScriptViewModel;
}
