#pragma once
#include "Widgets/SCompoundWidget.h"


class FStackSystemManager;

class SStackGraphPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SStackGraphPanel) {}
		SLATE_ARGUMENT(TSharedPtr<FStackSystemManager>, SystemManager)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	TSharedPtr<FStackSystemManager> SystemManager;

	TSharedPtr<SGraphEditor> GraphEditor;

	TSharedRef<SWidget> CreateContextMenu();
	FReply HandleAddStack();

	// Optional: expose hooks or delegates for Designer to extend
};
