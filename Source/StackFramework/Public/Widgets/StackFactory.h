#pragma once
#include "Templates/SharedPointer.h"



class FPanelSubTabViewModel;

class FStackFactory
{
public:
	static FStackFactory& Get();

	TSharedRef<SWidget> CreateStackView(TSharedRef<FPanelSubTabViewModel> ViewModel);

private:
	FStackFactory() = default;
};