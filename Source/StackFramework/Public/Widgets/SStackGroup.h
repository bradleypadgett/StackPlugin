#pragma once
#include "Widgets/SStackEntry.h"
#include "Layout/Visibility.h"



class UStackGroup;
class UStackRootViewModel;
class UStackEntry;

class STACKFRAMEWORK_API SStackGroup : public SStackEntry
{
public:
	SLATE_BEGIN_ARGS(SStackGroup) {}
	SLATE_END_ARGS();

	void Construct(const FArguments& InArgs, UStackGroup& InGroup, UStackRootViewModel* InStackRootViewModel);

private:
	TSharedRef<SWidget> ConstructAddButton();

	FText GetDeleteButtonToolTip() const;

	EVisibility GetDeleteButtonVisibility() const;

	FReply DeleteClicked();

	void OnCheckStateChanged(ECheckBoxState InCheckState);
	ECheckBoxState CheckEnabledStatus() const;
	bool GetEnabledCheckBoxEnabled() const;

	FReply AddClicked();
	FText GetAddButtonToolTip() const;

private:
	UStackGroup* Group;
};
