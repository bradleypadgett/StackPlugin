#include "Widgets/SStackList.h"
#include "ViewModels/StackRoot.h"
#include "ViewModels/Editor/StackSelectionViewModel.h"
#include "Widgets/SStackEntry.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Views/SListView.h"
#include "ViewModels/Editor/StackRootViewModel.h"



void SStackList::Construct(const FArguments& InArgs, UStackRootViewModel* InRootViewModel, UStackRoot* InRoot, UStackSelectionViewModel* InSelection)
{
	Root = InRoot;
	RootViewModel = InRootViewModel;
	SelectionViewModel = InSelection;

	RefreshEntries();

	ChildSlot
		[
			SNew(SVerticalBox)

				// Header List View
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SAssignNew(HeaderList, SListView<TSharedRef<UStackRootViewModel::FStackRootContainer>>)
						.ListItemsSource(&RootContainers)
						.OnGenerateRow_Lambda([](TSharedRef<UStackRootViewModel::FStackRootContainer> RootContainer, const TSharedRef<STableViewBase>& OwnerTable)
							{
								return SNew(STableRow<TSharedRef<UStackRootViewModel::FStackRootContainer>>, OwnerTable)
									[
										SNew(STextBlock).Text(RootContainer->DisplayName)
									];
							})
				]

			// Entry Tree View
			+ SVerticalBox::Slot()
				.FillHeight(1.f)
				[
					SAssignNew(Tree, STreeView<UStackEntry*>)
						.TreeItemsSource(&RootEntries)
						.OnGenerateRow_Lambda([](UStackEntry* Entry, const TSharedRef<STableViewBase>& OwnerTable)
							{
								return SNew(STableRow<UStackEntry*>, OwnerTable)
									[
										SNew(STextBlock).Text(Entry ? Entry->GetDisplayName() : FText::FromString("<Invalid>")) 
									];
							})
						.OnGetChildren_Lambda([](UStackEntry* Parent, TArray<UStackEntry*>& OutChildren)
							{
								if (Parent)
								{
									OutChildren = Parent->GetChildren(); // You may need to expose this
								}
							})
				]
		];
}


void SStackList::RefreshEntries()
{
	RootContainers.Reset();
	RootEntries.Reset();

	if (RootViewModel)
	{
		// Add stack root entries
		RootEntries.Append(RootViewModel->GetRootEntries());

		// Add top-level stack headers (for pinned tabs, etc.)
		for (const UStackRootViewModel::FStackRootContainer& RootContainer : RootViewModel->GetRootContainers())
		{
			RootContainers.Add(MakeShared<UStackRootViewModel::FStackRootContainer>(RootContainer));
		}
	}

	if (HeaderList.IsValid())
	{
		HeaderList->RequestListRefresh();
	}
	if (Tree.IsValid())
	{
		Tree->RequestTreeRefresh();
	}
}

TSharedRef<ITableRow> SStackList::OnGenerateRow(UStackEntry* Entry, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<UStackEntry*>, OwnerTable)
		[
			SNew(SStackEntry, Entry, SelectionViewModel)
		];
}

void SStackList::OnSelectionChanged(UStackEntry* Entry, ESelectInfo::Type SelectInfo)
{
	//if (SelectionViewModel)
	//{
	//	SelectionViewModel->SetSelectedEntry(Entry);
	//}
}

