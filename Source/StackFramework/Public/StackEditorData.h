#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StackEditorData.generated.h"



UCLASS()
class STACKFRAMEWORK_API UStackEditorData : public UObject
{
	GENERATED_BODY()

public:
	bool GetIsExpanded(const FString& StackEntryKey, bool bDefault = false) const;
	void SetIsExpanded(const FString& StackEntryKey, bool bExpanded);

	bool GetIsRenamePending(const FString& StackEntryKey) const;
	void SetIsRenamePending(const FString& StackEntryKey, bool bRenamePending);

	double GetLastScrollPosition() const;
	void SetLastScrollPosition(double InScrollPosition);

private:
	UPROPERTY()
	TMap<FString, bool> ExpandedMap;

	UPROPERTY()
	TMap<FString, bool> RenamePendingMap;

	UPROPERTY()
	double LastScrollPosition = 0.0;
};
