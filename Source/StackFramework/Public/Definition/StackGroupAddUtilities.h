#pragma once
#include "Internationalization/Text.h"
#include "Misc/Optional.h"



class FStackAddAction;

/*
 * Interface for Stack item groups that support dynamic Add (+) buttons.
 */
class IStackGroupAddUtilities
{
public:
	enum class EAddMode
	{
		AddDirectly,
		AddFromActionList,
	};

	virtual ~IStackGroupAddUtilities() {}

	/** Name shown in the Add menu, e.g., "Parameter" or "Module". */
	virtual FText GetAddItemName() const = 0;

	/** Whether the Add label ("Add Parameter") is shown next to the button. */
	virtual bool GetShowLabel() const = 0;

	/** Whether to expand all actions by default in the search popup. */
	virtual bool GetAutoExpandAddActions() const = 0;

	/** Returns how Add works: directly or from search. */
	virtual EAddMode GetAddMode() const = 0;

	/** Called if mode is AddDirectly. */
	virtual void AddItemDirectly() = 0;

	/** Populates list of searchable add actions. */
	virtual void GenerateAddActions(TArray<TSharedRef<FStackAddAction>>& OutActions) const = 0;

	/** Executes a selected action. */
	virtual void ExecuteAddAction(TSharedRef<FStackAddAction> Action, int32 TargetIndex) = 0;
};

/**
 * Represents a single add action (for searchable menu).
 */
class FStackAddAction : public TSharedFromThis<FStackAddAction>
{
public:
	FStackAddAction(FText InDisplayName, FText InDescription, FText InKeywords)
		: DisplayName(MoveTemp(InDisplayName))
		, Description(MoveTemp(InDescription))
		, Keywords(MoveTemp(InKeywords))
	{
	}

	FText GetDisplayName() const { return DisplayName; }
	FText GetDescription() const { return Description; }
	FText GetKeywords() const { return Keywords; }

private:
	FText DisplayName;
	FText Description;
	FText Keywords;
};
