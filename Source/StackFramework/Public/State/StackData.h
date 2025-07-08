#pragma once
#include "State/StackDataBase.h"
#include "StackData.generated.h"



class UStackEditorData;

UCLASS()
class UStackData : public UStackDataBase
{
	GENERATED_BODY()

public:
	UStackData(const FObjectInitializer& ObjectInitializer);

	virtual void PostLoad() override;

	UStackEditorData& GetEditorData() const;

private:
	UPROPERTY(Instanced)
	TObjectPtr<UStackEditorData> EditorData;
};
