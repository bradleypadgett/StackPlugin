#include "ViewModels/Editor/StackSystemViewModel.h"
#include "State/StackSystemState.h"
#include "State/StackEditorState.h"
#include "ViewModels/StackRoot.h"
#include "ViewModels/Editor/StackHandleViewModel.h"
#include "ViewModels/Editor/StackViewModel.h"
#include "Stack.h"
#include "StackNode.h"
#include "Widgets/SBoxPanel.h"



FStackSystemViewModel::FStackSystemViewModel()
{

}

void FStackSystemViewModel::Initialize(TScriptInterface<IStackSource> InStackSource)
{
	SetStackSource(InStackSource);
}

void FStackSystemViewModel::SetStackSource(TScriptInterface<IStackSource> InStackSource)
{
	check(InStackSource);
	StackSource = InStackSource;
}

IStackSource* FStackSystemViewModel::GetStackSource() const
{
	check(StackSource);
	return StackSource.GetInterface();
}

UStackSystemState& FStackSystemViewModel::GetSystemState() const
{
	return *SystemState;
}

void FStackSystemViewModel::AddStackSource(TScriptInterface<IStackSource> InStackSource)
{
	if (InStackSource)
	{
		StackSources.AddUnique(InStackSource);
	}
}

TArray<TScriptInterface<IStackSource>> FStackSystemViewModel::GetAllStackSources() const
{
	TArray<TScriptInterface<IStackSource>> Result;
	//for (auto& WeakStack : StackSources)
	//{
	//	if (TScriptInterface<IStackSource> TempStack = WeakStack.Get())
	//	{
	//		Result.Add(TempStack);
	//	}
	//}
	return Result;
}

UStackSelectionViewModel* FStackSystemViewModel::GetSelectionViewModel() const
{
	return SelectionViewModel;
}

TSharedPtr<FStackHandleViewModel> FStackSystemViewModel::GetHandleViewModelFromID(const FGuid& InHandleID) const
{
	for (const TSharedRef<FStackHandleViewModel>& Handle : HandleViewModels)
	{
		if (Handle->GetHandleID() == InHandleID)
		{
			return Handle;
		}
	}
	return nullptr;
}

TSharedPtr<FStackHandleViewModel> FStackSystemViewModel::GetHandleViewModelFromStack(const UStack& InStack) const
{
	/*if (UStackEditorState* StackEditorState = InStack.GetStackEditorState())
	{
		for (TSharedRef<FStackHandleViewModel> Handle : HandleViewModels)
		{
			if (StackState == Handle->GetStackViewModel()->GetStack().GetStackEditorState())
			{
				return Handle;
			}
		}
	}*/
	return nullptr;
}



void FStackSystemViewModel::SetActiveStackSource(TScriptInterface<IStackSource> InStackSource)
{
	ActiveStackSource = InStackSource;
}

TScriptInterface<IStackSource> FStackSystemViewModel::GetActiveStackSource() const
{
	return ActiveStackSource;
}

void FStackSystemViewModel::SetSelectedEntry(UStackEntry* InEntry)
{
	SelectedEntry = InEntry;
}

UStackEntry* FStackSystemViewModel::GetSelectedEntry() const
{
	return SelectedEntry.Get();
}

TSharedRef<SWidget> FStackSystemViewModel::CreatePaletteWidget()
{
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(STextBlock).Text(FText::FromString(TEXT("🧩 Palette (stub)")))
		];
}
