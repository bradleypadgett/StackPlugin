#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StackSelectionViewModel.generated.h"



class UStackEntry;

DECLARE_MULTICAST_DELEGATE(FOnEntrySelectionChanged);

UCLASS()
class STACKFRAMEWORK_API UStackSelectionViewModel : public UObject
{
	GENERATED_BODY()

public:
	void Initialize();

	void SetSelectedEntry(UStackEntry* Entry);
	UStackEntry* GetSelectedEntry() const;

	FOnEntrySelectionChanged& OnEntrySelectionChanged();

private:
	UPROPERTY()
	TObjectPtr<UStackEntry> SelectedEntry;

	FOnEntrySelectionChanged EntrySelectionChangedDelegate;
};
