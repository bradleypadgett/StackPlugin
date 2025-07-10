#include "StackHandle.h"
#include "Definition/StackSource.h"
#include "Stack.h"



FStackHandle::FStackHandle()
	: bIsEnabled(true)
{
}

FStackHandle::FStackHandle(const TScriptInterface<IStackSource>& InStackSource)
	: StackSource(InStackSource)
	, ID(FGuid::NewGuid())
	, Name(InStackSource->GetStack().GetUniqueName())
	, bIsEnabled(true)
{
}

bool FStackHandle::IsValid() const
{
	return ID.IsValid() && GetSource() != nullptr;
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
	if (GetSource())
	{
		GetStack().Rename(*NewName.ToString());
	}
}
