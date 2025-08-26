#include "StackHandle.h"
#include "Providers/StackSource.h"
#include "Stack.h"



FStackHandle::FStackHandle()
	: bIsEnabled(true)
{
}

/*FStackHandle::FStackHandle(const TScriptInterface<IStackSource>& InStackSource)
	: StackSource(InStackSource)
	, ID(FGuid::NewGuid())
	, Name(InStackSource->GetStack().GetUniqueStackName())
	, bIsEnabled(true)
{
}*/

FStackHandle::FStackHandle(UStack& InStack)
	: Stack(&InStack)
	, ID(FGuid::NewGuid())
	, Name(InStack.GetUniqueStackName())
	, bIsEnabled(true)
{
}

bool FStackHandle::IsValid() const
{
	return ID.IsValid();// && GetSource() != nullptr;
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
	return;
}

TObjectPtr<UStack> FStackHandle::GetStack()
{
	return Stack;
}
