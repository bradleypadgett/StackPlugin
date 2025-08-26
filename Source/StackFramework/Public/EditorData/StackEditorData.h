#pragma once
#include "StackEditorData.generated.h"


// TO-DO ~ Store Stack node positions
class UStackRootEditorData;

UCLASS()
class UStackEditorData : public UObject
{
	GENERATED_BODY()

public:
	UStackEditorData(const FObjectInitializer& ObjectInitializer);

	virtual void PostLoad() override;

	UStackRootEditorData& GetRootEditorData() const;

	void RootEditorDataChanged();
	FSimpleMulticastDelegate& OnPersistentDataChanged() { return PersistentDataChangedDelegate; }

private:
	FSimpleMulticastDelegate PersistentDataChangedDelegate;

	// Stack holds a ref to the entry data
	UPROPERTY(Instanced)
	TObjectPtr<UStackRootEditorData> RootEditorData;
};
