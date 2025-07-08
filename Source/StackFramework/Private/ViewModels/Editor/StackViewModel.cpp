#include "ViewModels/Editor/StackViewModel.h"
#include "ViewModels/Editor/StackHandleViewModel.h"
#include "State/StackData.h"



FStackViewModel::FStackViewModel()
{

}

FStackViewModel::~FStackViewModel()
{

}

UStackData& FStackViewModel::GetStackData()
{
	return *GetMutableDefault<UStackData>();
}

UStack& FStackViewModel::GetStack()
{
	// TO-DO ~ weak ptr check
	return *Stack;
}

TSharedPtr<FStackHandleViewModel> FStackViewModel::GetHandleViewModel(const FStackHandleViewModel& InHandleViewModel) const
{
	return HandleViewModel;
}
