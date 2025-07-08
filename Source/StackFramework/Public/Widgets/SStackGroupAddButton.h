#pragma once
#include "Widgets/SCompoundWidget.h"



class UStackEntry;
class IStackGroupAddUtilities;
class SComboButton;

class SStackGroupAddButton : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SStackGroupAddButton) {}
	SLATE_END_ARGS();

	void Construct(const FArguments& InArgs, UStackEntry* InSourceEntry, IStackGroupAddUtilities* InAddUtilities);

private:
	TSharedRef<SWidget> GetAddMenu();
	FReply AddDirectlyClicked();

private:
	TWeakObjectPtr<UStackEntry> SourceEntryWeak;
	IStackGroupAddUtilities* AddUtilities = nullptr;
	TSharedPtr<SComboButton> AddActionButton;
};
