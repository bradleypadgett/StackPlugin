#pragma once



class FStackHandleViewModel;
class UStackEditorState;
class UStackViewState;
class IStackSource;

// TO~DO - mayyybe add viewmodel manager for all these viewmodels
class FStackViewModel : public TSharedFromThis<FStackViewModel>
{
public:
	FStackViewModel();
	~FStackViewModel();

	void Initialize(TScriptInterface<IStackSource> InStackSource);

	UStackEditorState* GetStackEditorState() const;
	UStackViewState& GetStackViewState() const;
	IStackSource* GetStackSource() const;

	TSharedPtr<FStackHandleViewModel> GetHandleViewModel(const FStackHandleViewModel& InHandleViewModel) const;

private:

	UPROPERTY()
	TScriptInterface<IStackSource> StackSource;

	TSharedPtr<FStackHandleViewModel> HandleViewModel;

};
