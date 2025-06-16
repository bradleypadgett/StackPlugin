#include "Widgets/StackUtilities.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/STableRow.h"
#include "ViewModels/StackEntry.h"



FName FStackEditorUtilities::GetColorForCategory(FName Category)
{
	return FName("StackEditor.Category.DefaultColor");
}

bool FStackEditorUtilities::AddContextMenuActions(FMenuBuilder& MenuBuilder, UStackEntry* StackEntry)
{
	// Placeholder stub
	return false;
}



TSharedRef<FDragDropOperation> FStackEditorUtilities::CreateDragDropOperation(const TArray<UStackEntry*>& Entries)
{
	return FStackEntryDragDropOp::New(Entries);
}

void FStackEditorUtilities::HandleDragLeave(const FDragDropEvent& InDragDropEvent)
{

}

UStackEntry::FDropRequestResponse FStackEditorUtilities::RequestDropZone(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, UStackEntry* TargetEntry)
{
	TOptional<EItemDropZone> DropZone;

	if (!InDragDropEvent.GetOperation().IsValid() || TargetEntry == nullptr) return DropZone;

	TSharedPtr<FDecoratedDragDropOp> DecoratedOp = InDragDropEvent.GetOperationAs<FDecoratedDragDropOp>();
	if (DecoratedOp.IsValid())
	{
		DecoratedOp->ResetToDefaultToolTip();
	}

	UStackEntry::EDragOptions DragOptions = UStackEntry::EDragOptions::None;
	if (InDragDropEvent.IsAltDown() && !InDragDropEvent.IsShiftDown() && !InDragDropEvent.IsControlDown())
	{
		DragOptions = UStackEntry::EDragOptions::Copy;
	}

	UStackEntry::FDropRequest Request(
		InDragDropEvent.GetOperation().ToSharedRef(),
		InDropZone,
		DragOptions,
		UStackEntry::EDropOptions::None
	);

	TOptional<UStackEntry::FDropRequestResponse> Response = TargetEntry->CanDrop(Request);
	if (Response.IsSet())
	{
		if (DecoratedOp.IsValid() && !Response->DropMessage.IsEmptyOrWhitespace())
		{
			DecoratedOp->CurrentHoverText = Response->DropMessage;
		}

		if (Response->DropZone.IsSet())
		{
			DropZone = Response->DropZone.GetValue();
		}
		else if (DecoratedOp.IsValid())
		{
			DecoratedOp->CurrentIconBrush = FAppStyle::GetBrush("Icons.Error");
			DecoratedOp->CurrentIconColorAndOpacity = FLinearColor::White;
		}
	}
	return DropZone;
}

bool FStackEditorUtilities::HandleDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, UStackEntry* TargetEntry)
{
	TSharedPtr<FStackEntryDragDropOp> DragOp = InDragDropEvent.GetOperationAs<FStackEntryDragDropOp>();
	if (!DragOp.IsValid() || TargetEntry == nullptr)
	{
		return false;
	}

	// Temp - just loggin' what was dropped
	for (TWeakObjectPtr<UStackEntry> Entry : DragOp->DraggedEntries)
	{
		if (Entry.IsValid())
		{
			UE_LOG(LogTemp, Log, TEXT("Dropped '%s' onto '%s' at zone %d"), *Entry->GetName(), *TargetEntry->GetName(), (int32)InDropZone);
		}
	}

	// Actual insert logic will go here eventually
	return true;
}

FString FStackEditorUtilities::EntryToDebugString(UStackEntry* Entry)
{
	return FString(TEXT("[Entry debug stub]"));
}
