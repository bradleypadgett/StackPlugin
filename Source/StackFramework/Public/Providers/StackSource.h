#pragma once
#include "UObject/Interface.h"
#include "StackSource.generated.h"

/*
* This interface is to abstract UStacks a bit for allowing flexibility of stack types.
* 
* As in, later on I'm planning on implementing a UStackInstance (like material instances) as well as
* special UStackNodes (such as a K2 node which wraps a UStack).
*
* This'll allow each stack type to have a centralized place for getting their actual UStacks underneath !
*/
class UStack;
class UStackEditorData;
class UStackSystem;

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
