#include "StackHandle.h"
#include "Stack.h"



FStackHandle::FStackHandle()
	: bIsEnabled(true)
{
}

FStackHandle::FStackHandle(UStack& InStack)
	: ID(FGuid::NewGuid())
	, Name(*InStack.GetUniqueName())
	, Stack(&InStack)
	, bIsEnabled(true)
{
}

bool FStackHandle::IsValid() const
{
	return ID.IsValid() && Stack != nullptr;
}

FGuid FStackHandle::GetHandleID() const
{
	return ID;
}

FName FStackHandle::GetName() const
{
	return Name;
}

void FStackHandle::SetName(FName NewName)
{
	Name = NewName;
	if (Stack)
	{
		Stack->Rename(*NewName.ToString());
	}
}

UStack* FStackHandle::GetStack() const
{
	return Stack;
}
