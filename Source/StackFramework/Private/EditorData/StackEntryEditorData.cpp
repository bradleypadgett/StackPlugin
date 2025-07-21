#include "EditorData/StackEntryEditorData.h"



bool UStackEntryEditorData::GetIsExpanded(const FString& StackEntryKey, bool bDefault) const
{
	if (const bool* bFound = ExpandedMap.Find(StackEntryKey))
	{
		return *bFound;
	}
	return bDefault;
}

void UStackEntryEditorData::SetIsExpanded(const FString& StackEntryKey, bool bExpanded)
{
	ExpandedMap.Add(StackEntryKey, bExpanded);
}

bool UStackEntryEditorData::GetIsExpandedInNode(const FString& StackEntryKey, bool bIsExpandedDefault) const
{
	const bool* bIsExpandedPtr = KeyToExpandedNodeMap.Find(StackEntryKey);
	return bIsExpandedPtr != nullptr ? *bIsExpandedPtr : bIsExpandedDefault;
}

void UStackEntryEditorData::SetIsExpandedInNode(const FString& StackEntryKey, bool bIsExpanded)
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

bool UStackEntryEditorData::GetIsRenamePending(const FString& StackEntryKey) const
{
	if (const bool* bFound = RenamePendingMap.Find(StackEntryKey))
	{
		return *bFound;
	}
	return false;
}

void UStackEntryEditorData::SetIsRenamePending(const FString& StackEntryKey, bool bRenamePending)
{
	RenamePendingMap.Add(StackEntryKey, bRenamePending);
}

double UStackEntryEditorData::GetLastScrollPosition() const
{
	return LastScrollPosition;
}

void UStackEntryEditorData::SetLastScrollPosition(double InScrollPosition)
{
	LastScrollPosition = InScrollPosition;
}
