#pragma once
#include "StackSystemEditorData.generated.h"



class UStackEditorData;

UCLASS()
class STACKFRAMEWORK_API UStackSystemEditorData : public UObject
{
	GENERATED_BODY()

public:
	UStackEditorData& GetStackEditorData(/* TO-DO ~ Add Handle */) const { return *StackEditorData; }

private:
	UPROPERTY()
	TObjectPtr<UStackEditorData> StackEditorData;
};
