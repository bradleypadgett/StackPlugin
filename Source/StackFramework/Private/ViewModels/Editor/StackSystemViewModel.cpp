#include "ViewModels/Editor/StackSystemViewModel.h"
#include "State/StackSystemData.h"
#include "State/StackData.h"
#include "ViewModels/StackRoot.h"
#include "Definition/StackEditorDataProvider.h"
#include "ViewModels/Editor/StackHandleViewModel.h"
#include "ViewModels/Editor/StackViewModel.h"
#include "Stack.h"
#include "StackNode.h"
#include "Widgets/SBoxPanel.h"



FStackSystemViewModel::FStackSystemViewModel()
{

}

void FStackSystemViewModel::Initialize(UStack* InStack)
{
	SetStack(InStack);
}

void FStackSystemViewModel::SetStack(UStack* InStack)
{
	check(InStack);
	check(InStack->GetClass()->ImplementsInterface(UStackEditorDataProvider::StaticClass()));
	Stack = InStack;
}

UStack* FStackSystemViewModel::GetStack() const
{
	check(Stack);
	return Stack;
}

// Take the editor data for this system, and treat it as a UStackSystemData. Crash if it's not.
UStackSystemData& FStackSystemViewModel::GetSystemData() const
{
	check(Stack);
	const IStackEditorDataProvider* Provider = Cast<IStackEditorDataProvider>(Stack);
	checkf(Provider, TEXT("Asset must implement IStackEditorDataProvider"));
	return *CastChecked<UStackSystemData>(Provider->GetEditorData());
}

void FStackSystemViewModel::AddStack(UStack* InStack)
{
	if (InStack)
	{
		Stacks.AddUnique(InStack);
	}
}

TArray<UStack*> FStackSystemViewModel::GetAllStacks() const
{
	TArray<UStack*> Result;
	for (auto& WeakStack : Stacks)
	{
		if (UStack* TempStack = WeakStack.Get())
		{
			Result.Add(TempStack);
		}
	}
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
	/*if (UStackData* StackData = InStack.GetStackData())
	{
		for (TSharedRef<FStackHandleViewModel> Handle : HandleViewModels)
		{
			if (StackData == Handle->GetStackViewModel()->GetStack().GetStackData())
			{
				return Handle;
			}
		}
	}*/
	return nullptr;
}



void FStackSystemViewModel::SetActiveStack(UStack* InStack)
{
	ActiveStack = InStack;
}

UStack* FStackSystemViewModel::GetActiveStack() const
{
	return ActiveStack.Get();
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
