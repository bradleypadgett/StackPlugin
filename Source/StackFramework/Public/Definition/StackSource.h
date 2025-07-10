#pragma once
#include "UObject/Interface.h"
#include "StackSource.generated.h"



class UStack;
class UStackEditorState;

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
	virtual UStackEditorState* GetStackEditorState() const = 0;
};
