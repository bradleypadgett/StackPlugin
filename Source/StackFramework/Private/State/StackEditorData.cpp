#include "State/StackEditorData.h"



bool UStackEditorData::GetIsExpanded(const FString& StackEntryKey, bool bDefault) const
{
	if (const bool* bFound = ExpandedMap.Find(StackEntryKey))
	{
		return *bFound;
	}
	return bDefault;
}

void UStackEditorData::SetIsExpanded(const FString& StackEntryKey, bool bExpanded)
{
	ExpandedMap.Add(StackEntryKey, bExpanded);
}

bool UStackEditorData::GetIsExpandedInNode(const FString& StackEntryKey, bool bIsExpandedDefault) const
{
	const bool* bIsExpandedPtr = KeyToExpandedNodeMap.Find(StackEntryKey);
	return bIsExpandedPtr != nullptr ? *bIsExpandedPtr : bIsExpandedDefault;
}

void UStackEditorData::SetIsExpandedInNode(const FString& StackEntryKey, bool bIsExpanded)
{
	bool bBroadcast = false;
	if (ensureMsgf(StackEntryKey.IsEmpty() == false, TEXT("Can not set the expanded state with an empty key")))
	{
		bBroadcast = GetIsExpandedInNode(StackEntryKey, true) != bIsExpanded;
		KeyToExpandedNodeMap.FindOrAdd(StackEntryKey) = bIsExpanded;
	}

	if (bBroadcast)
	{
		OnPersistentDataChanged().Broadcast();
	}
}

bool UStackEditorData::GetIsRenamePending(const FString& StackEntryKey) const
{
	if (const bool* bFound = RenamePendingMap.Find(StackEntryKey))
	{
		return *bFound;
	}
	return false;
}

void UStackEditorData::SetIsRenamePending(const FString& StackEntryKey, bool bRenamePending)
{
	RenamePendingMap.Add(StackEntryKey, bRenamePending);
}

double UStackEditorData::GetLastScrollPosition() const
{
	return LastScrollPosition;
}

void UStackEditorData::SetLastScrollPosition(double InScrollPosition)
{
	LastScrollPosition = InScrollPosition;
}
