#include "Widgets/SStackView.h"
#include "Widgets/SStackList.h"
#include "ViewModels/Editor/StackViewModel.h"
#include "ViewModels/Editor/StackSelectionViewModel.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"



void SStackView::Construct(const FArguments& InArgs)
{
	StackViewModel = InArgs._StackViewModel;
	SelectionViewModel = InArgs._SelectionViewModel;

	ChildSlot
		[
			SNew(SVerticalBox)

				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(STextBlock)
						.Text(FText::FromString("Stack View"))
				]

				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				[
					SAssignNew(StackList, SStackList)
						.StackViewModel(StackViewModel)
						.SelectionViewModel(SelectionViewModel)
				]
		];
}

SStackView::~SStackView() {}
