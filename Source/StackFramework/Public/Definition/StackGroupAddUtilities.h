#pragma once
#include "Internationalization/Text.h"
#include "Misc/Optional.h"



class FStackAddAction;

/*
 * Interface for utilities that allow a stack group to support Add (+) functionality.
 */
class IStackGroupAddUtilities
{
public:
	enum class EAddMode
	{
		AddDirectly,
		AddFromActionList
	};

	virtual ~IStackGroupAddUtilities() {}

	virtual FText GetAddItemName() const = 0;
	virtual bool GetShowLabel() const = 0;
	virtual bool GetAutoExpandAddActions() const = 0;
	virtual EAddMode GetAddMode() const = 0;

	virtual void AddItemDirectly() = 0;
	virtual void GenerateAddActions(TArray<TSharedRef<FStackAddAction>>& OutActions) const = 0;
	virtual void ExecuteAddAction(TSharedRef<FStackAddAction> Action, int32 TargetIndex) = 0;

	virtual bool SupportsLibraryFilter() const { return false; }
	virtual bool SupportsSourceFilter() const { return false; }
};

/*
 * Base implementation of the IStackGroupAddUtilities interface.
 */
class FStackGroupAddUtilities : public IStackGroupAddUtilities
{
public:
	FStackGroupAddUtilities(FText InAddItemName, EAddMode InAddMode, bool bInAutoExpandAddActions, bool bInShowLabel)
		: AddItemName(MoveTemp(InAddItemName))
		, bShowLabel(bInShowLabel)
		, bAutoExpandAddActions(bInAutoExpandAddActions)
		, AddMode(InAddMode)
	{
	}

	virtual FText GetAddItemName() const override { return AddItemName; }
	virtual bool GetShowLabel() const override { return bShowLabel; }
	virtual bool GetAutoExpandAddActions() const override { return bAutoExpandAddActions; }
	virtual EAddMode GetAddMode() const override { return AddMode; }

protected:
	FText AddItemName;
	bool bShowLabel;
	bool bAutoExpandAddActions;
	EAddMode AddMode;
};

/*
 * Represents a single searchable add action in a group's add list.
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

// A templated helper that wraps a static utility struct for group add logic
template<typename StaticUtilityStructType>
class TStackGroupAddUtilities final : public FStackGroupAddUtilities
{
public:
	TStackGroupAddUtilities()
		: FStackGroupAddUtilities(
			StaticUtilityStructType::GetAddItemName(),
			StaticUtilityStructType::GetAddMode(),
			StaticUtilityStructType::GetAutoExpandAddActions(),
			StaticUtilityStructType::GetShowLabel())
	{
	}

	virtual void AddItemDirectly() override
	{
		StaticUtilityStructType::StaticExecuteAdd();
	}

	virtual void GenerateAddActions(TArray<TSharedRef<FStackAddAction>>& OutActions) const override
	{
		StaticUtilityStructType::StaticGenerateAddActions(OutActions);
	}

	virtual void ExecuteAddAction(TSharedRef<FStackAddAction> Action, int32 TargetIndex) override
	{
		StaticUtilityStructType::StaticExecuteAction(Action, TargetIndex);
	}
};