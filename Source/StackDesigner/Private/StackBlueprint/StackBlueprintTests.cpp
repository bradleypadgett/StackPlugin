#include "StackBlueprintTests.h"
#include "Widgets/Text/STextBlock.h"



void SStackBlueprintPlaceholderWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(STextBlock).Text(FText::FromString(TEXT("Placeholder Tab")))
	];
}
