#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StackViewState.generated.h"



UCLASS()
class STACKFRAMEWORK_API UStackViewState : public UObject
{
	GENERATED_BODY()

public:
	bool GetIsExpanded(const FString& StackEntryKey, bool bDefault = false) const;
	void SetIsExpanded(const FString& StackEntryKey, bool bExpanded);

	bool GetIsRenamePending(const FString& StackEntryKey) const;
	void SetIsRenamePending(const FString& StackEntryKey, bool bRenamePending);

	double GetLastScrollPosition() const;
	void SetLastScrollPosition(double InScrollPosition);

	bool GetIsExpandedInNode(const FString& StackEntryKey, bool bIsExpandedDefault) const;
	void SetIsExpandedInNode(const FString& StackEntryKey, bool bIsExpanded);

#if WITH_EDITORONLY_DATA
	virtual void PostLoadFromOwner(UObject* InOwner) {}

	FSimpleMulticastDelegate& OnPersistentDataChanged() { return PersistentDataChangedDelegate; }

private:
	FSimpleMulticastDelegate PersistentDataChangedDelegate;
#endif

private:
	UPROPERTY()
	TMap<FString, bool> ExpandedMap;

	UPROPERTY()
	TMap<FString, bool> RenamePendingMap;

	UPROPERTY()
	TMap<FString, bool> KeyToExpandedNodeMap;
	
	UPROPERTY()
	double LastScrollPosition = 0.0;
};
