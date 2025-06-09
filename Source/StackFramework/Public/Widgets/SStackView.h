#pragma once
#include "Widgets/SCompoundWidget.h"



class UStackViewModel;
class UStackSelectionViewModel;
class SStackList;

class SStackView : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SStackView) {}
		SLATE_ARGUMENT(UStackViewModel*, StackViewModel)
		SLATE_ARGUMENT(UStackSelectionViewModel*, SelectionViewModel)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual ~SStackView() override;

private:
	UStackViewModel* StackViewModel = nullptr;
	UStackSelectionViewModel* SelectionViewModel = nullptr;

	TSharedPtr<SStackList> StackList;
};
