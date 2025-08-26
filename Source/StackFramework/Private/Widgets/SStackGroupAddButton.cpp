#include "Widgets/SStackGroupAddButton.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SComboButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SImage.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "ViewModels/StackEntry.h"
#include "Utilities/StackGroupAddUtilities.h"



#define LOCTEXT_NAMESPACE "SStackGroupAddButton"

void SStackGroupAddButton::Construct(const FArguments& InArgs, UStackEntry* InSourceEntry, IStackGroupAddUtilities* InAddUtilities)
{
	SourceEntryWeak = InSourceEntry;
	AddUtilities = InAddUtilities;

	TSharedPtr<SWidget> ButtonContent;

	if (AddUtilities->GetShowLabel())
	{
		ButtonContent = SNew(STextBlock)
			.Text(FText::Format(LOCTEXT("AddItem", "+ Add {0}"), AddUtilities->GetAddItemName()));
	}
	else
	{
		ButtonContent = SNew(SImage)
			.Image(FAppStyle::Get().GetBrush("Icons.Plus"));
	}

	TSharedPtr<SWidget> Content;

	if (AddUtilities->GetAddMode() == IStackGroupAddUtilities::EAddMode::AddFromActionList)
	{
		Content = SAssignNew(AddActionButton, SComboButton)
			.ToolTipText(FText::Format(LOCTEXT("AddToGroupFormat", "Add a new {0} to this group."), AddUtilities->GetAddItemName()))
			.HasDownArrow(false)
			.OnGetMenuContent(this, &SStackGroupAddButton::GetAddMenu)
			.ContentPadding(1.0f)
			.ButtonContent()[ ButtonContent.ToSharedRef() ];
	}
	else
	{
		Content = SNew(SButton)
			.ToolTipText(FText::Format(LOCTEXT("AddToGroupFormat", "Add a new {0} to this group."), AddUtilities->GetAddItemName()))
			.ContentPadding(1.0f)
			.OnClicked(this, &SStackGroupAddButton::AddDirectlyClicked)
			.Content()[ ButtonContent.ToSharedRef() ];
	}

	ChildSlot [ Content.ToSharedRef() ];
}

TSharedRef<SWidget> SStackGroupAddButton::GetAddMenu()
{
	// TO-DO ~ Later hook up actual search/filter UI
	return SNew(STextBlock).Text(LOCTEXT("Stub", "Search menu not yet implemented"));
}

FReply SStackGroupAddButton::AddDirectlyClicked()
{
	if (SourceEntryWeak.IsValid())
	{
		AddUtilities->AddItemDirectly();
		SourceEntryWeak->SetIsExpandedInNode(true);
	}
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
