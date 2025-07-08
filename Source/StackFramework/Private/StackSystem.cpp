#include "StackSystem.h"
#include "Stack.h"
#include "StackHandle.h"



UStackSystem::UStackSystem()
{
	Name = NAME_None;
}

void UStackSystem::AddHandle(FStackHandle& InNewHandle)
{
	if (InNewHandle.IsValid() && !StackHandles.Contains(InNewHandle))
	{
		StackHandles.Add(InNewHandle);
	}
}

void UStackSystem::RemoveHandle(FStackHandle& InHandleToRemove)
{
	StackHandles.Remove(InHandleToRemove);
}
