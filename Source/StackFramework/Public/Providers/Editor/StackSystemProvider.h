#pragma once
#include "UObject/Interface.h"
#include "StackSystemProvider.generated.h"



class UStackSystem;
class FStackSystemManager;

UINTERFACE(MinimalAPI)
class UStackSystemProvider : public UInterface
{
    GENERATED_BODY()
};

class IStackSystemProvider
{
    GENERATED_BODY()

public:

    virtual UStackSystem* GetStackSystem() const = 0;
    virtual TSharedPtr<FStackSystemManager> GetStackSystemManager() const = 0;

};
