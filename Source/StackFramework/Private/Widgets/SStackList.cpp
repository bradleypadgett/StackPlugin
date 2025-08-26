#include "Widgets/SStackList.h"
#include "ViewModels/StackRoot.h"
#include "ViewModels/Editor/StackSelectionManager.h"
#include "Widgets/SStackEntry.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Views/SListView.h"
#include "ViewModels/Editor/StackRootManager.h"



void SStackList::Construct(const FArguments& InArgs, UStackRootManager* InRootManager, UStackRoot* InRoot, UStackSelectionManager* InSelection)
{
	Root = InRoot;
	RootManager = InRootManager;
	SelectionManager = InSelection;

	RefreshEntries();

	ChildSlot
		[
			SNew(SVerticalBox)

				// Header List View
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SAssignNew(HeaderList, SListView<TSharedRef<UStackRootManager::FStackRootContainer>>)
						.ListItemsSource(&RootContainers)
						.OnGenerateRow_Lambda([](TSharedRef<UStackRootManager::FStackRootContainer> RootContainer, const TSharedRef<STableViewBase>& OwnerTable)
							{
								return SNew(STableRow<TSharedRef<UStackRootManager::FStackRootContainer>>, OwnerTable)
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

	if (RootManager)
	{
		// Add stack root entries
		RootEntries.Append(RootManager->GetRootEntries());

		// Add top-level stack headers (for pinned tabs, etc.)
		for (const UStackRootManager::FStackRootContainer& RootContainer : RootManager->GetRootContainers())
		{
			RootContainers.Add(MakeShared<UStackRootManager::FStackRootContainer>(RootContainer));
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
			SNew(SStackEntry, Entry, SelectionManager)
		];
}

void SStackList::OnSelectionChanged(UStackEntry* Entry, ESelectInfo::Type SelectInfo)
{
	//if (SelectionManager)
	//{
	//	SelectionManager->SetSelectedEntry(Entry);
	//}
}

