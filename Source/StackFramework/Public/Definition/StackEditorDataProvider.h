#pragma once
#include "UObject/Interface.h"
#include "StackEditorDataProvider.generated.h"



class UStackDataBase;

/*
 * Interface for assets or objects that can provide editor-only stack metadata.
 * 
 * Implement this on any UObject that you want to support being edited by the StackFramework.
 * Your object will be expected to return a pointer to a UStackDataBase instance,
 * which stores persistent editor state such as expansion, selection, issues, etc.
 */
UINTERFACE()
class STACKFRAMEWORK_API UStackEditorDataProvider : public UInterface
{
	GENERATED_BODY()
};

class STACKFRAMEWORK_API IStackEditorDataProvider
{
	GENERATED_BODY()

public:
	/*
	 * Return the stack-related editor data for this object.
	 * This should return a valid UStackDataBase-derived object.
	 */
	virtual UStackDataBase* GetEditorData() const = 0;
};
