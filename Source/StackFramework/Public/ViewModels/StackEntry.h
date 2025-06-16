#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DragAndDrop/DecoratedDragDropOp.h"
#include "Widgets/Views/STableRow.h"
#include "StackEntry.generated.h"



class UStackEntry;

class FStackEntryDragDropOp : public FDecoratedDragDropOp
{
public:
	DRAG_DROP_OPERATOR_TYPE(FStackEntryDragDropOp, FDecoratedDragDropOp)

		TArray<TWeakObjectPtr<UStackEntry>> DraggedEntries;

	static TSharedRef<FStackEntryDragDropOp> New(const TArray<UStackEntry*>& InEntries)
	{
		TSharedRef<FStackEntryDragDropOp> DragDropOp = MakeShareable(new FStackEntryDragDropOp);
		for (UStackEntry* Entry : InEntries)
		{
			DragDropOp->DraggedEntries.Add(Entry);
		}

		DragDropOp->DefaultHoverText = FText::FromString(TEXT("Move Entry"));
		DragDropOp->DefaultHoverIcon = FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.ArrowRight").GetIcon();
		DragDropOp->Construct();

		return DragDropOp;
	}
};


/*
 * Base class for all stack viewmodels and items.
 * Supports nesting, display names, expansion, and refresh behavior.
 */
UCLASS()
class STACKFRAMEWORK_API UStackEntry : public UObject
{
	GENERATED_BODY()

public:
	enum class EIconMode {Brush, Text, None };

	enum class EDragOptions {Copy, None};
	enum class EDropOptions {Overview, None};

	struct FDropRequest
	{
		FDropRequest(TSharedRef<const FDragDropOperation> InDragDropOperation, EItemDropZone InDropZone, EDragOptions InDragOptions, EDropOptions InDropOptions)
			: DragDropOperation(InDragDropOperation)
			, DropZone(InDropZone)
			, DragOptions(InDragOptions)
			, DropOptions(InDropOptions)
		{
		}

		const TSharedRef<const FDragDropOperation> DragDropOperation;
		const EItemDropZone DropZone;
		const EDragOptions DragOptions;
		const EDropOptions DropOptions;
	};

	struct FDropRequestResponse
	{
		FDropRequestResponse(TOptional<EItemDropZone> InZone, FText InMessage = FText())
			: DropZone(InZone), DropMessage(InMessage) {}

		const TOptional<EItemDropZone> DropZone;
		const FText DropMessage;
	};

public:
	UStackEntry();

	virtual void RefreshChildren();

	virtual FText GetDisplayName() const;

	virtual bool GetCanExpand() const;

	virtual bool GetShouldShowInStack() const;

	const TArray<UStackEntry*>& GetChildren() const;

	//remove later
	void SetDisplayName(FText Name) { DisplayName = Name; };

	virtual TOptional<FDropRequestResponse> CanDrop(const FDropRequest& Request) const
	{
		// TEMP logic: allow drop by default
		return FDropRequestResponse(Request.DropZone, FText());
	}


protected:
	virtual void RefreshChildrenInternal(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren);

protected:
	UPROPERTY()
	TArray<TObjectPtr<UStackEntry>> Children;

	UPROPERTY()
	FText DisplayName;
};
