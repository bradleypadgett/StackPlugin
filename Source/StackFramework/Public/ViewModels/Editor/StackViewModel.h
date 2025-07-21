#pragma once



class FStackScriptViewModel;
class FStackHandleViewModel;
class UStackEditorData;
class IStackSource;

// TO~DO - mayyybe add viewmodel manager for all these viewmodels
class FStackViewModel : public TSharedFromThis<FStackViewModel>
{
public:
	FStackViewModel();
	~FStackViewModel();

	void Initialize(TScriptInterface<IStackSource> InStackSource);

	UStackEditorData& GetStackEditorData() const;
	IStackSource* GetStackSource() const;

	TSharedPtr<FStackHandleViewModel> GetHandleViewModel(const FStackHandleViewModel& InHandleViewModel) const;
	TSharedRef<FStackScriptViewModel> GetScriptViewModel();

private:

	UPROPERTY()
	TScriptInterface<IStackSource> StackSource;

	TSharedPtr<FStackHandleViewModel> HandleViewModel;
	TSharedRef<FStackScriptViewModel> ScriptViewModel;

};
