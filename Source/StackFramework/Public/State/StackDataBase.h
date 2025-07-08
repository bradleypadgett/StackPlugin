#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StackDataBase.generated.h"



/*
 * A base class for editor-only data which supports post loading from the runtime owner object.
 */
UCLASS(Abstract)
class STACKFRAMEWORK_API UStackDataBase : public UObject
{
	GENERATED_BODY()

public:
#if WITH_EDITORONLY_DATA
	virtual void PostLoadFromOwner(UObject* InOwner) {}

	FSimpleMulticastDelegate& OnPersistentDataChanged() { return PersistentDataChangedDelegate; }

private:
	FSimpleMulticastDelegate PersistentDataChangedDelegate;
#endif
};
