#include "Widgets/StackFactory.h"
#include "Widgets/Text/STextBlock.h"



FStackFactory& FStackFactory::Get()
{
	static FStackFactory Instance;
	return Instance;
}

TSharedRef<SWidget> FStackFactory::CreateStackView(TSharedRef<FPanelSubTabViewModel> ViewModel)
{
	return SNew(STextBlock).Text(FText::FromString("[StackView Placeholder]"));
}