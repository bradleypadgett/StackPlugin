#pragma once
#include "UObject/Interface.h"
#include "StackSource.generated.h"



class UStack;
class UStackEditorData;

UINTERFACE(MinimalAPI, BlueprintType)
class UStackSource : public UInterface
{
	GENERATED_BODY()
};

class IStackSource
{
	GENERATED_BODY()

public:
	virtual UStack& GetStack() = 0;
	virtual const UStack& GetStack() const = 0;
	virtual UStackEditorData* GetStackEditorData() const = 0;
};
