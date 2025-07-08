#pragma once



class UStackData;
class FStackViewModel;
class FStackHandleViewModel;
class UStack;

// TO~DO - mayyybe add viewmodel manager for all these viewmodels
class FStackViewModel : public TSharedFromThis<FStackViewModel>
{
public:
	FStackViewModel();
	~FStackViewModel();

	UStackData& GetStackData();
	UStack& GetStack();

	TSharedPtr<FStackHandleViewModel> GetHandleViewModel(const FStackHandleViewModel& InHandleViewModel) const;

private:

	TSharedPtr<FStackHandleViewModel> HandleViewModel;

	// TO-DO ~ Store as weak ptr
	UPROPERTY()
	UStack* Stack;
	//TWeakPtr<UStack> StackWeakPtr;
};
