#pragma once
#include "Widgets/SCompoundWidget.h"



/*
 *  A placeholder widget used during tab layout testing.
 */
class SStackBlueprintPlaceholderWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SStackBlueprintPlaceholderWidget) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
};