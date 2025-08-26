#include "Widgets/SStackGroup.h"
#include "Styling/AppStyle.h"
#include "ViewModels/StackGroup.h"
#include "Widgets/SStackGroupAddButton.h"
#include "ViewModels/Editor/StackRootManager.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/SBoxPanel.h"



#define LOCTEXT_NAMESPACE "StackGroup"

void SStackGroup::Construct(const FArguments& InArgs, UStackGroup& InGroup, UStackRootManager* InStackRootManager)
{
	Group = &InGroup;
	StackEntry = Group;

	TSharedRef<SHorizontalBox> RowBox = SNew(SHorizontalBox);

	// Name block
	RowBox->AddSlot()
		.VAlign(VAlign_Center)
		.Padding(2, 0, 0, 0)
		[
			// TO-DO ~ Add SStackDisplayName
			//SNew(SStackDisplayName, InGroup)
			SNew(STextBlock)
				.Text(FText::FromString(TEXT("<Unnamed>")))
		];

	// Delete button
	if (Group->SupportsDelete())
	{
		RowBox->AddSlot()
			.AutoWidth()
			.Padding(0, 0, 2, 0)
			[
				SNew(SButton)
					.ButtonStyle(FAppStyle::Get(), "HoverHintOnly")
					.IsFocusable(false)
					.ToolTipText(this, &SStackGroup::GetDeleteButtonToolTip)
					.OnClicked(this, &SStackGroup::DeleteClicked)
					.Visibility(this, &SStackGroup::GetDeleteButtonVisibility)
					.Content()
					[
						SNew(SImage)
							.Image(FAppStyle::Get().GetBrush("Icons.Delete"))
							.ColorAndOpacity(FSlateColor::UseForeground())
					]
			];
	}

	// Enabled checkbox
	if (Group->SupportsChangeEnabled())
	{
		RowBox->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			[
				SNew(SCheckBox)
					.IsChecked(this, &SStackGroup::CheckEnabledStatus)
					.OnCheckStateChanged(this, &SStackGroup::OnCheckStateChanged)
					.IsEnabled(this, &SStackGroup::GetEnabledCheckBoxEnabled)
			];
	}

	// Add Button
	if (Group->SupportsAdd())
	{
		RowBox->AddSlot()
			.AutoWidth()
			.HAlign(HAlign_Right)
			.Padding(2, 0, 0, 0)
			[
				ConstructAddButton()
			];
	}

	ChildSlot
		[
			RowBox
		];
}

TSharedRef<SWidget> SStackGroup::ConstructAddButton()
{
	IStackGroupAddUtilities* AddUtilities = Group->GetAddUtilities();
	if (AddUtilities != nullptr)
	{
		return SNew(SStackGroupAddButton, Group, AddUtilities);
	}
	return SNullWidget::NullWidget;
}

FText SStackGroup::GetDeleteButtonToolTip() const
{
	FText Message;
	Group->TestCanDeleteWithMessage(Message);
	return Message;
}

EVisibility SStackGroup::GetDeleteButtonVisibility() const
{
	FText UnusedMessage;
	return Group->SupportsDelete() && Group->TestCanDeleteWithMessage(UnusedMessage)
		? EVisibility::Visible
		: EVisibility::Collapsed;
}

FReply SStackGroup::DeleteClicked()
{
	Group->Delete();
	return FReply::Handled();
}

void SStackGroup::OnCheckStateChanged(ECheckBoxState InCheckState)
{
	Group->SetIsEnabled(InCheckState == ECheckBoxState::Checked);
}

ECheckBoxState SStackGroup::CheckEnabledStatus() const
{
	return Group->GetIsEnabled() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

bool SStackGroup::GetEnabledCheckBoxEnabled() const
{
	return Group->GetOwnerIsEnabled();
}

#undef LOCTEXT_NAMESPACE
