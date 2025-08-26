#pragma once
#include "StackSystemEditorData.generated.h"



class UStackRootEditorData;
class UStackSystem;

UCLASS()
class STACKFRAMEWORK_API UStackSystemEditorData : public UObject
{
	GENERATED_BODY()

public:
	virtual void PostInitProperties() override;

	UStackRootEditorData& GetSystemRootEditorData() const { return *SystemRootEditorData; }

	UEdGraph* GetSystemGraph();

	bool GetIsGraphEnabled() { return bIsGraphEnabled; }
	void SetIsGraphEnabled(bool bEnabled) { bIsGraphEnabled = bEnabled; }

	void SyncSystemGraph(UStackSystem& InSystem);

private:
	UPROPERTY(Instanced)
	TObjectPtr<UStackRootEditorData> SystemRootEditorData;

	UPROPERTY()
	TObjectPtr<UEdGraph> SystemGraph;

	UPROPERTY()
	bool bIsGraphEnabled = true;
};
