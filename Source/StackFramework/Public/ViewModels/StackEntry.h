#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DragAndDrop/DecoratedDragDropOp.h"
#include "Widgets/Views/STableRow.h"
#include "Definition/StackCommonTypes.h"
#include "StackEntry.generated.h"



class UStackEntry;
class UStackViewState;
class FStackSystemViewModel;
class FStackViewModel;

UENUM()
enum class EIssueSeverity : uint8
{
	Error = 0,
	Warning,
	Info,
	None
};

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
	enum class EDropOptions {Node, None};

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

	struct FStackSearchItem
	{
		UPROPERTY()
		FName Key;

		UPROPERTY()
		FText Value;

		bool operator==(const FStackSearchItem& Other) const
		{
			return Key == Other.Key && Value.ToString() == Other.Value.ToString();
		}
	};

	struct FCategoryNames
	{
		static const FName Default;
		static const FName Node;

	};

	struct FSubcategoryNames
	{
		static const FName Default;
		static const FName Settings;
	};

	struct FStackEntryContext
	{
		FStackEntryContext(TSharedRef<FStackSystemViewModel> InSystemViewModel, TSharedPtr<FStackViewModel> InStackViewModel, FName InCategoryName, FName InSubcategoryName, UStackViewState& InStackViewState)
			: SystemViewModel(InSystemViewModel)
			, StackViewModel(InStackViewModel)
			, CategoryName(InCategoryName)
			, SubcategoryName(InSubcategoryName)
			, StackViewState(&InStackViewState)
		{
		}

		const TSharedRef<FStackSystemViewModel> SystemViewModel;
		const TSharedPtr<FStackViewModel> StackViewModel;
		const FName CategoryName;
		const FName SubcategoryName;
		UStackViewState* const StackViewState;
	};

	struct FStackIssue
	{
		// TO-DO ~ Fill in issue data later (severity, message, fix delegate)
	};

	DECLARE_MULTICAST_DELEGATE(FOnExpansionChanged);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnStructureChanged, EStackStructureChangedFlags);

public:

	UStackEntry();

	void Initialize(FStackEntryContext InStackEntryContext, FString InStackStateKey);
	//void Finalize();
	bool IsFinalized() const;
	
protected:
	virtual void FinalizeInternal();

public:
	virtual FText GetDisplayName() const;

	//remove later
	void SetDisplayName(FText Name) { DisplayName = Name; };

	UStackViewState& GetStackViewState() const;
	FString GetStackViewStateKey() const;

	virtual FText GetTooltipText() const;

	virtual bool GetCanExpand() const;
	virtual bool GetCanExpandInNode() const;

	// TO-DO ~ Flesh out both of these in .cpp later
	virtual bool GetIsExpanded() const { return bExpanded; }
	virtual void SetIsExpanded(bool bInExpanded) { bExpanded = bInExpanded; }

	bool GetIsExpandedInNode() const;
	void SetIsExpandedInNode(bool bInExpanded);

	virtual bool GetIsEnabled() const;
	bool GetOwnerIsEnabled() const;

	bool GetIsEnabledAndOwnerIsEnabled() const { return GetIsEnabled() && GetOwnerIsEnabled(); }

	int32 GetIndentLevel() const;

	virtual bool GetShouldShowInStack() const;

	virtual bool SupportsAdd() const { return false; }
	virtual bool SupportsDelete() const { return false; }
	virtual void Delete() {}
	virtual bool TestCanDeleteWithMessage(FText& OutCanDeleteMessage) const { return false; }

protected:
	virtual void RefreshStackChildren(const TArray<UStackEntry*>& CurrentChildren, TArray<UStackEntry*>& NewChildren, TArray<FStackIssue>& NewIssues);

public:
	virtual void RefreshChildren();
	virtual bool HasAnyChildren() const { return Children.Num() > 0; }
	const TArray<UStackEntry*>& GetChildren() const;

	virtual int32 GetChildIndentLevel() const;

	const TArray<UStackEntry*>& GetFilteredChildren(TArray<UStackEntry*>& OutFilteredChildren) const;
	void GetFilteredChildrenOfTypes(TArray<UStackEntry*>& OutFilteredChildren, const TSet<UClass*>& AllowedClasses, bool bRecursive = false) const;

	template<typename ChildType, typename PredicateType>
	static ChildType* FindCurrentChildOfTypeByPredicate(const TArray<UStackEntry*>& CurrentChildren, PredicateType Predicate)
	{
		for (UStackEntry* CurrentChild : CurrentChildren)
		{
			ChildType* TypedCurrentChild = Cast<ChildType>(CurrentChild);
			if (TypedCurrentChild != nullptr && Predicate(TypedCurrentChild))
			{
				return TypedCurrentChild;
			}
		}
		return nullptr;
	}

	template<typename ChildType>
	static ChildType* FindCurrentChildOfType(const TArray<UStackEntry*>& CurrentChildren)
	{
		for (UStackEntry* CurrentChild : CurrentChildren)
		{
			ChildType* TypedCurrentChild = Cast<ChildType>(CurrentChild);
			if (TypedCurrentChild != nullptr)
			{
				return TypedCurrentChild;
			}
		}
		return nullptr;
	}

	FOnExpansionChanged& OnExpansionChanged();

	FOnExpansionChanged& OnExpansionInNodeChanged();

	FOnStructureChanged& OnStructureChanged();

	virtual void ChildStructureChangedInternal();

	TSharedRef<FStackSystemViewModel> GetSystemViewModel() const;
	TSharedPtr<FStackSystemViewModel> GetSystemViewModelPtr() const;
	TSharedPtr<FStackViewModel> GetStackViewModel() const;


	virtual TOptional<FDropRequestResponse> CanDrop(const FDropRequest& Request) const
	{
		// TEMP logic: allow drop by default
		return FDropRequestResponse(Request.DropZone, FText());
	}

	bool HasIssuesOrAnyChildHasIssues() const;

	int32 GetTotalNumberOfInfoIssues() const;
	int32 GetTotalNumberOfWarningIssues() const;
	int32 GetTotalNumberOfErrorIssues() const;
	const TArray<FStackIssue>& GetIssues() const;

protected:
	UPROPERTY()
	FText DisplayName;

	UPROPERTY()
	bool bExpanded = true;


private:
	FName CategoryName;
	FName SubcategoryName;

	UPROPERTY()
	TArray<TObjectPtr<UStackEntry>> Children;

	mutable bool bFilterChildrenPending;

	mutable TArray<UStackEntry*> FilteredChildren;


	TWeakPtr<FStackSystemViewModel> SystemViewModel;
	TWeakPtr<FStackViewModel> StackViewModel;

	UPROPERTY()
	TObjectPtr<UStackViewState> StackViewState;
	FString StackViewStateKey;

	FOnExpansionChanged ExpansionChangedDelegate;

	FOnExpansionChanged ExpansionInNodeChangedDelegate;

	mutable TOptional<bool> bIsExpandedCache;
	mutable TOptional<bool> bIsExpandedInNodeCache;

	int32 IndentLevel;

	TArray<FStackIssue> StackIssues;
	TArray<FStackIssue> ExternalStackIssues;

	FOnStructureChanged StructureChangedDelegate;

	bool bIsFinalized;

	bool bOwnerIsEnabled;
};

// TO-DO ~ Add in [class SStackSpacer : public UStackEntry] here!