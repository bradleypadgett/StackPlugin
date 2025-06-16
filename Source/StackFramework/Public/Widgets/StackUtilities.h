#pragma once
#include "CoreMinimal.h"
#include "Templates/SharedPointer.h"
#include "Input/Reply.h"
#include "ViewModels/StackEntry.h"
#include "Layout/Visibility.h"



class FMenuBuilder;
class SWidget;

namespace FStackEditorUtilities
{
	FName GetColorForCategory(FName Category);

	bool AddContextMenuActions(FMenuBuilder& MenuBuilder, UStackEntry* StackEntry);



	TSharedRef<FDragDropOperation> CreateDragDropOperation(const TArray<UStackEntry*>& Entries);

	void HandleDragLeave(const FDragDropEvent& InDragDropEvent);

	UStackEntry::FDropRequestResponse RequestDropZone(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, UStackEntry* TargetEntry);

	bool HandleDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, UStackEntry* TargetEntry);

	FString EntryToDebugString(UStackEntry* Entry);
}
