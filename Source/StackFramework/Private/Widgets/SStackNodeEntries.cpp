#include "Widgets/SStackNodeEntries.h"
#include "Widgets/SStackList.h"
#include "ViewModels/StackItem.h"
#include "ViewModels/StackEntry.h"
#include "ViewModels/Editor/StackRootViewModel.h"
#include "Definition/StackCommonTypes.h"
#include "ViewModels/StackRoot.h"
#include "ViewModels/Editor/StackSelectionViewModel.h"
#include "State/StackViewState.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Templates/SharedPointer.h"
#include "Misc/Optional.h"



class SStackNodeRow : public STableRow<UStackEntry*>
{
public:
	SLATE_BEGIN_ARGS(SStackNodeRow)
		: _Style(&GetDefaultStyle())
		{}
		SLATE_STYLE_ARGUMENT(FTableRowStyle, Style)
		SLATE_EVENT(FOnDragDetected, OnDragDetected)
		SLATE_EVENT(FOnTableRowDragLeave, OnDragLeave)
		SLATE_EVENT(FOnCanAcceptDrop, OnCanAcceptDrop)
		SLATE_EVENT(FOnAcceptDrop, OnAcceptDrop)
		SLATE_DEFAULT_SLOT(FArguments, Content)
	SLATE_END_ARGS();

	void Construct(const FArguments& InArgs, UStackEntry* InStackEntry, const TSharedRef<STableViewBase>& InOwnerTableView)
	{
		StackEntry = InStackEntry;
		// TO-DO ~ Add command context

		ExpandedImage = FCoreStyle::Get().GetBrush("TreeArrow_Expanded");
		CollapsedImage = FCoreStyle::Get().GetBrush("TreeArrow_Collapsed");

		StackEntry->OnStructureChanged().AddSP(this, &SStackNodeRow::InvalidateCachedData);

		TSharedPtr<SOverlay> RowOverlay;
		STableRow<UStackEntry*>::Construct(
			STableRow<UStackEntry*>::FArguments()
			.Style(InArgs._Style)
			.OnDragDetected(InArgs._OnDragDetected)
			.OnDragLeave(InArgs._OnDragLeave)
			.OnCanAcceptDrop(InArgs._OnCanAcceptDrop)
			.OnAcceptDrop(InArgs._OnAcceptDrop)
			[
				SAssignNew(RowOverlay, SOverlay)
					+ SOverlay::Slot()
					[
						SNew(SBorder)
							// TO-DO ~ Replace with Stack styling
							.BorderImage(FCoreStyle::Get().GetBrush("Border"))
							.ToolTipText_UObject(StackEntry, &UStackEntry::GetTooltipText)
							.Padding(FMargin(0, 0, 0, 1))
							[
								SNew(SHorizontalBox)
									+ SHorizontalBox::Slot()
									.AutoWidth()
									.VAlign(VAlign_Center)
									.HAlign(HAlign_Center)
									[
										SNew(SButton)
											// TO-DO ~ Replace with Stack styling
											.ButtonStyle(FCoreStyle::Get(), "NoBorder")
											.Visibility_Lambda([this]()
												{
													return StackEntry->GetCanExpandInNode() && GetChildEntryAmount() > 0
														? EVisibility::Visible
														: EVisibility::Collapsed;
												})
											.OnClicked_Lambda([this]()
												{
													const bool bWillExpand = !StackEntry->GetIsExpandedInNode();
													FScopedTransaction Transaction(bWillExpand
														? NSLOCTEXT("Stack", "Expand", "Expand Entry")
														: NSLOCTEXT("Stack", "Collapse", "Collapse Entry"));

													StackEntry->GetStackViewState().Modify();
													StackEntry->SetIsExpandedInNode(bWillExpand);
													return FReply::Handled();
												})
											.ContentPadding(FMargin(0.0f, 1.0f))
											[
												SNew(SImage)
													.Image(this, &SStackNodeRow::GetExpandButtonImage)
													.ColorAndOpacity(FSlateColor::UseForeground())
											]
									]
								+ SHorizontalBox::Slot()
									.Padding(TAttribute<FMargin>(this, &SStackNodeRow::GetInnerContentPadding))
									[
										InArgs._Content.Widget
									]
							]
					]
				+ SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					[
						SNew(SBorder)
							.BorderImage(FAppStyle::Get().GetBrush("WhiteBrush"))
							.BorderBackgroundColor(this, &SStackNodeRow::GetIssueHighlightColor)
							.Visibility_Static(&SStackNodeEntries::GetIssueIconVisibility, StackEntry)
							.Padding(FMargin(0, 0, 0, 1))
							[
								SNew(SBox).WidthOverride(2).HeightOverride(10)
							]
					]
			],
			InOwnerTableView
		);

		// Optional left highlight bar
		if (StackEntry->IsA<UStackItem>())
		{
			RowOverlay->AddSlot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(0))
				[
					SNew(SBorder)
						.BorderImage(FAppStyle::Get().GetBrush("WhiteBrush"))
						.BorderBackgroundColor(FSlateColor::UseSubduedForeground())
						.Padding(FMargin(0))
						[
							SNew(SBox).WidthOverride(2)
						]
				];
		}
	}

	virtual ~SStackNodeRow() override
	{
		if (StackEntry)
		{
			StackEntry->OnStructureChanged().RemoveAll(this);
		}
	}

	static const FTableRowStyle& GetDefaultStyle()
	{
		// TO-DO ~ Replace with Stack's registered style
		return FAppStyle::Get().GetWidgetStyle<FTableRowStyle>("TableView.Row");
	}

	// TO-DO ~ OnMouseButtonDown()

	// TO-DO ~ OnMouseButtonUp()
	 
	// TO-DO ~ OnMouseButtonDoubleClick()

private:
	const FSlateBrush* GetExpandButtonImage() const
	{
		return StackEntry->GetIsExpandedInNode() ? ExpandedImage : CollapsedImage;
	}

	FMargin GetInnerContentPadding() const
	{
		// TO-DO ~ Parameterize later with a depth-aware layout i.e. FMargin(NestingDepth * 5.f, 1, 1, 1);
		const float LeftPadding = StackEntry->IsA<UStackItem>() ? 5.f : 0.f;
		return FMargin(LeftPadding, 1, 1, 1);
	}

	uint32 GetChildEntryAmount() const
	{
		if (!ChildrenCount.IsSet())
		{
			TArray<UStackEntry*> Children;
			StackEntry->GetFilteredChildrenOfTypes(Children, {UStackItem::StaticClass()});
			ChildrenCount = Children.Num();
		}
		return ChildrenCount.GetValue();
	}

	void InvalidateCachedData(EStackStructureChangedFlags Flags)
	{
		ChildrenCount.Reset();
		IssueColor.Reset();
	}

	FSlateColor GetIssueHighlightColor() const
	{
		if (!IssueColor.IsSet())
		{
			// TO-DO ~ Add in Error/Warning/Info issues to StackEntry. Might remove ~
			if (StackEntry->GetTotalNumberOfErrorIssues() > 0)
			{
				IssueColor = FStyleColors::AccentRed.GetSpecifiedColor().Desaturate(0.1f);
			}
			else if (StackEntry->GetTotalNumberOfWarningIssues() > 0)
			{
				IssueColor = FStyleColors::AccentYellow.GetSpecifiedColor().Desaturate(0.1f);
			}
			else if (StackEntry->GetTotalNumberOfInfoIssues() > 0)
			{
				IssueColor = FStyleColors::AccentBlue.GetSpecifiedColor().Desaturate(0.1f);
			}
			else
			{
				IssueColor = FStyleColors::Transparent;
			}
		}
		return IssueColor.GetValue();
	}

private:
	UStackEntry* StackEntry = nullptr;
	const FSlateBrush* ExpandedImage = nullptr;
	const FSlateBrush* CollapsedImage = nullptr;

	mutable TOptional<uint32> ChildrenCount;
	mutable TOptional<FSlateColor> IssueColor;
	TAttribute<EVisibility> IssueIconVisibility;

	// TO-DO ~ Add in StackCommandContext

};

class SStackNodeEnabledCheckBox : public SCompoundWidget
{
public:
	DECLARE_DELEGATE_OneParam(FOnCheckedChanged, bool /*bIsChecked*/);

	SLATE_BEGIN_ARGS(SStackNodeEnabledCheckBox) {}
		SLATE_ATTRIBUTE(bool, IsChecked)
		SLATE_EVENT(FOnCheckedChanged, OnCheckedChanged)
	SLATE_END_ARGS();

	void Construct(const FArguments& InArgs)
	{
		IsChecked = InArgs._IsChecked;
		OnCheckedChanged = InArgs._OnCheckedChanged;

		ChildSlot
			[
				SNew(SCheckBox)
					.OnCheckStateChanged(this, &SStackNodeEnabledCheckBox::OnButtonClicked)
					.IsChecked(this, &SStackNodeEnabledCheckBox::IsEnabled)
					.ToolTipText(FText::FromString(TEXT("Enable or disable this item.")))
			];
	}

private:
	void OnButtonClicked(ECheckBoxState InNewState)
	{
		OnCheckedChanged.ExecuteIfBound(IsChecked.IsBound() && !IsChecked.Get());
	}

	ECheckBoxState IsEnabled() const
	{
		if (IsChecked.IsBound())
		{
			return IsChecked.Get() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
		}
		return ECheckBoxState::Unchecked;
	}

private:
	TAttribute<bool> IsChecked;
	FOnCheckedChanged OnCheckedChanged;
};

class SStackNodeItemName : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SStackNodeItemName) {}
	SLATE_END_ARGS();

	void Construct(const FArguments& InArgs, UStackItem* InStackItem)
	{
		StackItem = InStackItem;
		StackItem->OnAlternateDisplayNameChanged().AddSP(this, &SStackNodeItemName::UpdateFromAlternateDisplayName);

		ChildSlot
			[
				SAssignNew(NameTextBlock, STextBlock)
					.Text(this, &SStackNodeItemName::GetItemDisplayName)
					.ToolTipText(this, &SStackNodeItemName::GetItemToolTip)
					.IsEnabled_UObject(StackItem.Get(), &UStackEntry::GetIsEnabledAndOwnerIsEnabled)
					.ColorAndOpacity(FSlateColor::UseForeground())
			];

		UpdateTextStyle();
	}

	~SStackNodeItemName()
	{
		if (StackItem.IsValid() && !StackItem->IsFinalized())
		{
			StackItem->OnAlternateDisplayNameChanged().RemoveAll(this);
		}
	}

private:
	void UpdateTextStyle()
	{
		if (NameTextBlock.IsValid())
		{
			// TODO: Replace with your plugin's style set
			const bool bHasAlt = StackItem->GetAlternateDisplayName().IsSet();
			NameTextBlock->SetTextStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>(
				bHasAlt ? "AlternateText" : "NormalText"));
		}
	}

	FText GetItemDisplayName() const
	{
		if (StackItem.IsValid() && !StackItem->IsFinalized())
		{
			return StackItem->GetAlternateDisplayName().IsSet()
				? StackItem->GetAlternateDisplayName().GetValue()
				: StackItem->GetDisplayName();
		}
		return FText::GetEmpty();
	}

	FText GetItemToolTip() const
	{
		if (StackItem.IsValid() && !StackItem->IsFinalized())
		{
			const FText Tooltip = StackItem->GetTooltipText();
			const TOptional<FText>& Alt = StackItem->GetAlternateDisplayName();

			if (Alt.IsSet())
			{
				const FText Combo = FText::Format(
					NSLOCTEXT("Stack", "AltNameFormat", "{0} ({1})"),
					Alt.GetValue(),
					StackItem->GetDisplayName());

				return Tooltip.IsEmptyOrWhitespace()
					? Combo
					: FText::Format(NSLOCTEXT("Stack", "AltNameTooltipFormat", "{0}\n\n{1}"), Combo, Tooltip);
			}

			return Tooltip;
		}
		return FText::GetEmpty();
	}

	void UpdateFromAlternateDisplayName()
	{
		if (!StackItem.IsValid() || StackItem->IsFinalized())
		{
			return;
		}

		UpdateTextStyle();
		ToolTipCache.Reset();
	}

private:
	TWeakObjectPtr<UStackItem> StackItem;
	TSharedPtr<STextBlock> NameTextBlock;

	mutable FText LastToolTipCache;
	mutable TOptional<FText> ToolTipCache;
};

void SStackNodeEntries::Construct(const FArguments& InArgs, UStackRootViewModel& InStackRootViewModel, UStackSelectionViewModel& InSelectionViewModel)
{
	AllowedClasses = InArgs._AllowedClasses;

	bUpdatingSelectionFromStack = false;
	bUpdatingStackFromSelection = false;

	StackRootViewModel = &InStackRootViewModel;
	SelectionViewModel = &InSelectionViewModel;

	// Bind viewmodel events
	StackRootViewModel->OnStructureChanged().AddSP(this, &SStackNodeEntries::EntryStructureChanged);
	StackRootViewModel->OnExpansionInNodeChanged().AddSP(this, &SStackNodeEntries::EntryExpansionChanged);
	SelectionViewModel->OnEntrySelectionChanged().AddSP(this, &SStackNodeEntries::UpdateSelection);

	// Main UI
	ChildSlot
		[
			SAssignNew(EntryListView, SListView<UStackEntry*>)
				.Clipping(EWidgetClipping::OnDemand)
				.ListItemsSource(&EntryList)
				.OnGenerateRow(this, &SStackNodeEntries::OnGenerateRowForEntry)
				.OnSelectionChanged(this, &SStackNodeEntries::OnSelectionChanged)
				.SelectionMode(ESelectionMode::Multi)
				//.OnItemToString_Debug_Static(...) // optional for debug logging
		];

	bRefreshEntryListPending = true;
	RefreshEntryList();
	UpdateSelection();
}


SStackNodeEntries::~SStackNodeEntries()
{
	if (StackRootViewModel != nullptr)
	{
		StackRootViewModel->OnStructureChanged().RemoveAll(this);
		StackRootViewModel->OnExpansionInNodeChanged().RemoveAll(this);
		StackRootViewModel->OnExpansionChanged().RemoveAll(this);
	}

	if (SelectionViewModel != nullptr)
	{
		SelectionViewModel->OnEntrySelectionChanged().RemoveAll(this);
	}
}

bool SStackNodeEntries::SupportsKeyboardFocus() const
{
	return true;
}

FReply SStackNodeEntries::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	return FReply::Unhandled();
}

void SStackNodeEntries::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (bRefreshEntryListPending)
	{
		RefreshEntryList();
		bRefreshEntryListPending = false;
	}
}

EVisibility SStackNodeEntries::GetIssueIconVisibility(UStackEntry* StackEntry)
{
	if (StackEntry != nullptr && StackEntry->IsFinalized() == false)
	{
		bool bDisplayIcon;
		if (StackEntry->IsA<UStackGroup>() && StackEntry->GetCanExpandInNode() && StackEntry->GetIsExpandedInNode())
		{
			// If the entry is a group and it can expand and it is expanded, we only want to show the stack issue icon if the group itself has issues.
			bDisplayIcon = StackEntry->GetIssues().Num() > 0;
		}
		else
		{
			bDisplayIcon = StackEntry->HasIssuesOrAnyChildHasIssues();
		}
		return bDisplayIcon ? EVisibility::Visible : EVisibility::Collapsed;
	}
	return EVisibility::Collapsed;
}

void SStackNodeEntries::RefreshEntryList()
{
	if (!bRefreshEntryListPending || !StackRootViewModel)
	{
		return;
	}

	EntryList.Reset();
	EntryToParentChain.Reset();

	UStackEntry* RootEntry = StackRootViewModel->GetRootEntry();
	checkf(RootEntry != nullptr, TEXT("Root entry was null."));

	TArray<UStackEntry*> RootChildren;
	RootEntry->GetFilteredChildren(RootChildren);

	for (UStackEntry* Child : RootChildren)
	{
		checkf(Child != nullptr, TEXT("Root entry child was null."));
		TArray<UStackEntry*> ParentChain;
		AddEntriesRecursive(*Child, EntryList, AllowedClasses, ParentChain);
	}

	bRefreshEntryListPending = false;

	if (EntryListView.IsValid())
	{
		EntryListView->RequestListRefresh();
		UpdateSelection();
	}
}

void SStackNodeEntries::EntryExpansionChanged()
{
	bRefreshEntryListPending = true;
}

void SStackNodeEntries::EntryExpansionInNodeChanged()
{
	bRefreshEntryListPending = true;
}

void SStackNodeEntries::EntryStructureChanged(EStackStructureChangedFlags Flags)
{
	bRefreshEntryListPending = true;
}

void SStackNodeEntries::AddEntriesRecursive(UStackEntry& EntryToAdd, TArray<UStackEntry*>& OutList, const TArray<UClass*>& AcceptableClasses, TArray<UStackEntry*> ParentChain)
{
	if (AcceptableClasses.ContainsByPredicate([&EntryToAdd](UClass* Class) { return EntryToAdd.IsA(Class); }))
	{
		OutList.Add(&EntryToAdd);
		EntryToParentChain.Add(&EntryToAdd, ParentChain);
	}

	if (EntryToAdd.GetIsExpandedInNode())
	{
		TArray<UStackEntry*> Children;
		EntryToAdd.GetFilteredChildren(Children);

		ParentChain.Add(&EntryToAdd);
		for (UStackEntry* Child : Children)
		{
			AddEntriesRecursive(*Child, OutList, AcceptableClasses, ParentChain);
		}
	}
}

void SStackNodeEntries::OnSelectionChanged(UStackEntry* InNewSelection, ESelectInfo::Type SelectInfo)
{
	if (!bUpdatingStackFromSelection)
	{
		TGuardValue<bool> Guard(bUpdatingSelectionFromStack, true);

		TArray<UStackEntry*> SelectedEntries;
		EntryListView->GetSelectedItems(SelectedEntries);

		TArray<UStackEntry*> DeselectedEntries;
		for (TWeakObjectPtr<UStackEntry> PrevEntry : PreviousSelection)
		{
			if (PrevEntry.IsValid() && !SelectedEntries.Contains(PrevEntry.Get()))
			{
				DeselectedEntries.Add(PrevEntry.Get());
			}
		}

		const bool bClearSelection = !FSlateApplication::Get().GetModifierKeys().IsControlDown();

		SelectionViewModel->UpdateSelectedEntries(SelectedEntries, DeselectedEntries, bClearSelection);

		PreviousSelection.Empty();
		for (UStackEntry* Selected : SelectedEntries)
		{
			PreviousSelection.Add(Selected);
		}

		// TO-DO ~ Hook up command context selection
	}
}


void SStackNodeEntries::UpdateSelection()
{
	if (!SelectionViewModel || bUpdatingSelectionFromStack)
	{
		return;
	}

	TGuardValue<bool> Guard(bUpdatingStackFromSelection, true);

	TArray<UStackEntry*> SelectedEntries;
	EntryListView->GetSelectedItems(SelectedEntries);

	TArray<UStackEntry*> DeselectedEntries;
	for (TWeakObjectPtr<UStackEntry> Prev : PreviousSelection)
	{
		if (Prev.IsValid() && !SelectedEntries.Contains(Prev.Get()))
		{
			DeselectedEntries.Add(Prev.Get());
		}
	}

	const bool bClearCurrentSelection = !FSlateApplication::Get().GetModifierKeys().IsControlDown();

	SelectionViewModel->UpdateSelectedEntries(SelectedEntries, DeselectedEntries, bClearCurrentSelection);

	PreviousSelection.Reset();
	for (UStackEntry* Entry : SelectedEntries)
	{
		PreviousSelection.Add(Entry);
	}
}

// TO-DO ~ Flesh this out a ton
TSharedRef<ITableRow> SStackNodeEntries::OnGenerateRowForEntry(UStackEntry* Entry, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(SStackNodeRow, Entry, OwnerTable)
		.Style(&FAppStyle::Get().GetWidgetStyle<FTableRowStyle>("TableView.Row"))
		[
			SNew(SStackNodeItemName, Cast<UStackItem>(Entry))
		];
}