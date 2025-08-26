#include "ViewModels/Editor/StackSelectionManager.h"
#include "ViewModels/Editor/StackSystemManager.h"
#include "ViewModels/Editor/StackRootManager.h"
#include "ViewModels/Editor/StackHandleManager.h"
#include "ViewModels/Editor/StackManager.h"
#include "EditorData/StackSystemEditorData.h"
#include "Providers/StackSource.h"
#include "ViewModels/StackSelection.h"
#include "ViewModels/StackEntry.h"



// helps gen.cpp files make UCLASS(), UFUNCTION(), UPROPERTY() stuff work correctly
#include UE_INLINE_GENERATED_CPP_BY_NAME(StackSelectionManager)

FGuid GetHandleIDFromEntry(UStackEntry* Entry)
{
	if (Entry->GetStackManager().IsValid())
	{
		TSharedPtr<FStackHandleManager> HandleManager = Entry->GetSystemManager()->GetHandleManagerFromStack(Entry->GetStackManager()->GetStackSource()->GetStack());
		if (HandleManager.IsValid())
		{
			return HandleManager->GetHandleID();
		}
	}
	return FGuid();
}

UStackSelectionManager::FSelectedEntry::FSelectedEntry(UStackEntry* SelectedEntry)
	: Entry(SelectedEntry)
	, HandleID(GetHandleIDFromEntry(SelectedEntry))
	, EntryEditorDataKey(SelectedEntry->GetEntryEditorDataKey())
{

}

void UStackSelectionManager::Initialize(TSharedRef<FStackSystemManager> InStackSystemManager)
{
	SystemManagerWeak = InStackSystemManager;

	// Creates new Stack Selection
	SelectionEntry = NewObject<UStackSelection>(this);
	SelectionEntry->Initialize(UStackEntry::FStackEntryContext(
		InStackSystemManager
		, TSharedPtr<FStackManager>()
		, UStackEntry::FCategoryNames::Default
		, UStackEntry::FSubcategoryNames::Default
		, InStackSystemManager->GetSystemEditorData().GetSystemRootEditorData()
	));

	// Wraps Selection with a dedicated Manager
	// Used to show what's selected in Node UI
	SelectedRootManager = NewObject<UStackRootManager>(this);
	SelectedRootManager->InitializeStack(SelectionEntry);

	bRefreshIsPending = false;
	bIsSystemNodeSelected = false;
}

bool UStackSelectionManager::ContainsEntry(UStackEntry* Entry) const
{
	for (const FSelectedEntry& SelectedEntry : SelectedEntries)
	{
		if (SelectedEntry.Entry == Entry) return true;
	}
	return false;
}

void UStackSelectionManager::GetSelectedEntries(TArray<UStackEntry*>& OutSelectedEntries) const
{
	for (const FSelectedEntry& SelectedEntry : SelectedEntries)
	{
		OutSelectedEntries.Add(SelectedEntry.Entry.Get());
	}
}

void UStackSelectionManager::UpdateSelectedEntries(const TArray<UStackEntry*>& InSelectedEntries, const TArray<UStackEntry*>& InDeselectedEntries,bool bClearSelection)
{
	bool bSelectionChanged = false;

	if (bClearSelection)
	{
		SelectedEntries.Empty();
		bSelectionChanged = true;
	}
	else
	{
		for (UStackEntry* Deselected : InDeselectedEntries)
		{
			if (ContainsEntry(Deselected))
			{
				DeselectEntryInternal(Deselected);
				bSelectionChanged = true;
			}
		}
	}

	for (UStackEntry* Selected : InSelectedEntries)
	{
		if (!ContainsEntry(Selected))
		{
			SelectedEntries.Add(FSelectedEntry(Selected));
			bSelectionChanged = true;
		}
	}

	if (bSelectionChanged)
	{
		UpdateExternalSelectionState();
	}
}

FOnEntrySelectionChanged& UStackSelectionManager::OnEntrySelectionChanged()
{
	return EntrySelectionChangedDelegate;
}

void UStackSelectionManager::DeselectEntryInternal(UStackEntry* InDeselectedEntry)
{
	SelectedEntries.RemoveAll([InDeselectedEntry](const FSelectedEntry& SelectionEntry)
	{ 
		if (SelectionEntry.Entry == InDeselectedEntry)
		{
			return true;
		} 
		return false;
	});
}

void UStackSelectionManager::UpdateExternalSelectionState()
{
	// TO-DO ~ Refactor
	// Prune child-of-selected entries
	TArray<UStackEntry*> PrunedEntries;
	for (const FSelectedEntry& Entry : SelectedEntries)
	{
		bool bIsChild = false;
		UObject* Outer = Entry.Entry->GetOuter();
		while (Outer != nullptr)
		{
			if (UStackEntry* OuterEntry = Cast<UStackEntry>(Outer))
			{
				if (ContainsEntry(OuterEntry))
				{
					bIsChild = true;
					break;
				}
				Outer = OuterEntry->GetOuter();
			}
			else
			{
				break;
			}
		}

		if (!bIsChild)
		{
			PrunedEntries.Add(Entry.Entry.Get());
		}
	}

	SelectionEntry->SetSelectedEntries(PrunedEntries);
	EntrySelectionChangedDelegate.Broadcast();
}
