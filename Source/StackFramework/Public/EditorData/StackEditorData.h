#pragma once
#include "StackEditorData.generated.h"



class UStackEntryEditorData;

UCLASS()
class UStackEditorData : public UObject
{
	GENERATED_BODY()

public:
	UStackEditorData(const FObjectInitializer& ObjectInitializer);

	virtual void PostLoad() override;

	UStackEntryEditorData& GetStackEntryEditorData() const;

	void StackEntryEditorDataChanged();
	FSimpleMulticastDelegate& OnPersistentDataChanged() { return PersistentDataChangedDelegate; }

private:
	FSimpleMulticastDelegate PersistentDataChangedDelegate;

	// Stack holds a ref to the entry data
	UPROPERTY(Instanced)
	TObjectPtr<UStackEntryEditorData> StackEntryEditorData;
};
