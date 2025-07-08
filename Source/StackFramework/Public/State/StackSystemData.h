#pragma once
#include "State/StackDataBase.h"
#include "StackSystemData.generated.h"



class UStackEditorData;

UCLASS()
class STACKFRAMEWORK_API UStackSystemData : public UStackDataBase
{
	GENERATED_BODY()

public:
	UStackEditorData& GetEditorData() const { return *EditorData; }

private:
	UPROPERTY()
	TObjectPtr<UStackEditorData> EditorData;
};
