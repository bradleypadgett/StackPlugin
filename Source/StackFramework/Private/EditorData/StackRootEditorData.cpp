#include "EditorData/StackRootEditorData.h"



bool UStackRootEditorData::GetIsExpanded(const FString& StackEntryKey, bool bDefault) const
{
	if (const bool* bFound = ExpandedMap.Find(StackEntryKey))
	{
		return *bFound;
	}
	return bDefault;
}

void UStackRootEditorData::SetIsExpanded(const FString& StackEntryKey, bool bExpanded)
{
	ExpandedMap.Add(StackEntryKey, bExpanded);
}

bool UStackRootEditorData::GetIsExpandedInNode(const FString& StackEntryKey, bool bIsExpandedDefault) const
{
	const bool* bIsExpandedPtr = KeyToExpandedNodeMap.Find(StackEntryKey);
	return bIsExpandedPtr != nullptr ? *bIsExpandedPtr : bIsExpandedDefault;
}

void UStackRootEditorData::SetIsExpandedInNode(const FString& StackEntryKey, bool bIsExpanded)
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

bool UStackRootEditorData::GetIsRenamePending(const FString& StackEntryKey) const
{
	if (const bool* bFound = RenamePendingMap.Find(StackEntryKey))
	{
		return *bFound;
	}
	return false;
}

void UStackRootEditorData::SetIsRenamePending(const FString& StackEntryKey, bool bRenamePending)
{
	RenamePendingMap.Add(StackEntryKey, bRenamePending);
}

double UStackRootEditorData::GetLastScrollPosition() const
{
	return LastScrollPosition;
}

void UStackRootEditorData::SetLastScrollPosition(double InScrollPosition)
{
	LastScrollPosition = InScrollPosition;
}
