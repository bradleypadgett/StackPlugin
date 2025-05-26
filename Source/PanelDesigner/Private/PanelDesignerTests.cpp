#include "PanelDesignerTests.h"
#include "Widgets/Text/STextBlock.h"



void SPanelDesignerPlaceholderWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(STextBlock).Text(FText::FromString(TEXT("Placeholder Tab")))
	];
}
