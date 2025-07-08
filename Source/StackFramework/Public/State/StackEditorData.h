#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StackDataBase.h"
#include "StackEditorData.generated.h"



UCLASS()
class STACKFRAMEWORK_API UStackEditorData : public UStackDataBase
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
